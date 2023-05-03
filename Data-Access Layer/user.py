# Class User: it creates user entity objects.

from logger_base import log

class User:
    def __init__(self, id_user = None, username = None, password = None) -> None:
        self._id_user = id_user
        self._username = username
        self._password = password

    @property
    def id_user(self):
        return self._id_user

    @id_user.setter
    def id_user(self, id_user):
        self._id_user = id_user

    @property
    def username(self):
        return self._username

    @username.setter
    def username(self, username):
        self._username = username

    @property
    def password(self):
        return self._password

    @password.setter
    def password(self, password):
        self._password = password

    def __str__(self) -> str:
        return f'''
                ID: {self._id_user}
                Username: {self._username}
                Password: {self._password}
                '''

#-------------------------------------------------------------------

if __name__ == '__main__':
    user1 = User(1, 'ccastillo', 'c123')
    log.debug(user1)

    # Simulating an INSERT: the id_user is not provided.
    user1 = User(username = 'cbenavides', password = 'cb123')
    log.debug(user1)

    # Simulating an DELETE: only the id_user is provided.
    user1 = User(id_user = 1)
    log.debug(user1)

#-------------------------------------------------------------------
