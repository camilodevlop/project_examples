# Class User DAO:
# DAO: Data Access Object
# CRUD: Create-Read-Update-Delete

from user import User
from cursor_pool import Cursor_Pool
from logger_base import log

class UserDAO:
    _SELECT = 'SELECT * FROM users ORDER BY id_user'    
    _INSERT = 'INSERT INTO users(username, password) VALUES (%s,%s)'
    _UPDATE = 'UPDATE users SET username = %s, password = %s WHERE id_user = %s'
    _DELETE = 'DELETE FROM users WHERE id_user = %s'

#-------------------------------------------------------------------

    @classmethod
    def select(cls):
        with Cursor_Pool() as cursor:
            cursor.execute(cls._SELECT)
            registers = cursor.fetchall()
            users = []
            for register in registers:
                user = User(register[0], register[1], register[2])
                users.append(user)

            return users
    
    @classmethod
    def insert(cls, user):
        with Cursor_Pool() as cursor:
            log.debug(f'User to be inserted: {user}')
            values = (user.username, user.password)
            cursor.execute(cls._INSERT, values)
            log.debug(f'Inserted user: {user}')
            return cursor.rowcount

    @classmethod
    def update(cls, user):
        with Cursor_Pool() as cursor:
            log.debug(f'User to be updated: {user}')
            values = (user.username, user.password, user.id_user)
            cursor.execute(cls._UPDATE, values)
            log.debug(f'Updated user: {user}')
            return cursor.rowcount

    @classmethod
    def delete(cls, user):
        with Cursor_Pool() as cursor:
            log.debug(f'User to be deleted: {user}')
            values = (user.id_user,)
            cursor.execute(cls._DELETE, values)
            log.debug(f'Deleted user: {user}')
            return cursor.rowcount
    
#-------------------------------------------------------------------

if __name__ == '__main__':

    # User object insertion.
    #user1 = User(username = 'cbenavides', password = 'cb123')
    #inserted_users = UserDAO.insert(user1)
    #log.debug(f'Number of inserted users: {inserted_users}')

    # User object update.
    #user1 = User(3, 'camilobenavides', 'camilo123')
    #updated_users = UserDAO.update(user1)
    #log.debug(f'Number of updated users: {updated_users}')

    # User object update.
    user1 = User(id_user = 3)
    deleted_users = UserDAO.delete(user1)
    log.debug(f'Number of deleted users: {deleted_users}')

    # User object selection.
    users = UserDAO.select()
    for user in users:
        log.debug(user)

#-------------------------------------------------------------------
