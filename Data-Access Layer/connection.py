# Class Connection.

from psycopg2 import pool
from logger_base import log
import sys

class Connection:

    _DATABASE = 'test_db'
    _USERNAME = 'postgres'
    _PASSWORD = 'admin'
    _DB_PORT = '5432'
    _HOST = '127.0.0.1'
    _MIN_CON = 1
    _MAX_CON = 5
    _pool = None

#-------------------------------------------------------------------

# Pool of connections.

    @classmethod
    def get_pool(cls):
        if cls._pool == None:
            try:
                cls._pool = pool.SimpleConnectionPool(cls._MIN_CON, cls._MAX_CON,
                                                      host = cls._HOST,
                                                      user = cls._USERNAME,
                                                      password = cls._PASSWORD,
                                                      port = cls._DB_PORT,
                                                      database = cls._DATABASE
                                                      )

                log.debug(f'Successful connection pool creation: {cls._pool}')
                return cls._pool

            except Exception as e:
                log.error(f'Something is wrong: {e}')
                sys.exit()
        else:
            return cls._pool
    
    @classmethod
    def get_connection(cls):
        connection = cls.get_pool().getconn()
        log.debug(f'The connection was obtained from pool: {connection}')
        return connection

    @classmethod
    def release_connection(cls, connection):
        cls.get_pool().putconn(connection)
        log.debug(f'Successful connection release: {connection}')

    @classmethod
    def close_pool(cls):
        cls.get_connection().closeall()

#-------------------------------------------------------------------

if __name__ == '__main__':
    connection1 = Connection.get_connection()
    Connection.release_connection(connection1)
    connection2 = Connection.get_connection()
    connection3 = Connection.get_connection()
    connection4 = Connection.get_connection()
    connection5 = Connection.get_connection()
    connection6 = Connection.get_connection()

#-------------------------------------------------------------------
