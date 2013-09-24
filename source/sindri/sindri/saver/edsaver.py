#encoding: utf-8
import logging
import datetime
from sqlalchemy import Table, MetaData, select, create_engine
import sqlalchemy
from sindri.saver.message import persist_message
from sindri.saver.utils import FunctionalError, TechnicalError



class EdRealtimeSaver(object):
    """
    Classe responsable de l'enregistrement en base de donnée des événements
    temps réel.
    """
    def __init__(self, config):
        self.__engine = create_engine(config.ed_connection_string)
        self.meta = MetaData(self.__engine)
        self.message_table = Table('message', self.meta, autoload=True,
                schema='realtime')
        self.localized_message_table = Table('localized_message', self.meta,
                autoload=True, schema='realtime')

    def persist_message(self, message):
        self.__persist(message, persist_message)


    def persist_at_perturbation(self, perturbation):
        print 'ok'
        #self.__persist(, persist_message)

    def __persist(self, item, callback):
        """
        fonction englobant toute la gestion d'erreur lié à la base de donnée
        et la gestion de la transaction associé

        :param item l'objet à enregistré
        :param callback fonction charger de l'enregistrement de l'objet
        à proprement parler dont la signature est (meta, conn, item)
        meta etant un objet MetaData
        conn la connection à la base de donnée
        item etant l'objet à enregistrer
        """
        logger = logging.getLogger('sindri')
        conn = None
        try:
            conn = self.__engine.connect()
            transaction = conn.begin()
        except sqlalchemy.exc.SQLAlchemyError, e:
            logger.exception('error durring transaction')
            raise TechnicalError('problem with databases: ' + str(e))

        try:
            callback(self.meta, conn, item)
            transaction.commit()
        except (sqlalchemy.exc.IntegrityError, sqlalchemy.exc.DataError), e:
            logger.exception('error durring transaction')
            transaction.rollback()
            raise FunctionalError(str(e))
        except sqlalchemy.exc.SQLAlchemyError, e:
            logger.exception('error durring transaction')
            if not e.connection_invalidated:
                transaction.rollback()
            raise TechnicalError('problem with databases: ' + str(e))
        except:
            logger.exception('error durring transaction')
            try:
                transaction.rollback()
            except:
                pass
            raise
        finally:
            if conn:
                conn.close()

