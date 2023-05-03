from logger_base import log
from connection import Connection

class Cursor_Pool:
    def __init__(self) -> None:
        self._connection = None
        self._cursor = None

    def __enter__(self):
        log.debug(f'Beginning of the \'with\' method: __enter__')
        self._connection = Connection.get_connection()
        self._cursor = self._connection.cursor()
        return self._cursor

    def __exit__(self, tp, value, traceback):
        log.debug(f'End of the \'with\' method: __end__')
        if value:
           self._connection.rollback()
           log.error(f'Error: rollback() was called -> {tp} {value} {traceback}')
        else:
            self._connection.commit()
            log.debug(f'Commit of the transaction.')

        self._cursor.close()
        Connection.release_connection(self._connection)

#-------------------------------------------------------------------

if __name__ == '__main__':
    with Cursor_Pool() as cursor:
        log.debug(f'Inside of the \'with\' block.')
        cursor.execute('SELECT * FROM users')
        log.debug(cursor.fetchall())

#-------------------------------------------------------------------
