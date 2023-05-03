# Logging management.

import logging as log

log.basicConfig(
                level = log.DEBUG,
                format = '%(asctime)s: %(levelname)s [%(filename)s: %(lineno)s %(message)s]',
                datefmt = '%I:%M:%S %p',
                handlers = [
                            log.FileHandler('data_leyer.log'),
                            log.StreamHandler()
                            ]
                )

if __name__ == '__main__':
    log.debug('DEBUG level message')
    log.info('INFO level message')
    log.warning('WARNING level message')
    log.error('ERROR level message')
    log.critical('CRITICAL level message')

#-------------------------------------------------------------------
