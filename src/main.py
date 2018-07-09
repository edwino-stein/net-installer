import sys
import platform
from GUI import createViewer
from Application import Application

def main(argv):
    
    arch = platform.architecture()[0]
    if arch == '64bit':
        arch = 'x64'
    elif arch == '32bit':
        arch = 'x86'
    else:
        arch = 'Desconhecida'

    app = Application(('pxe', 'gwh28dgcmp'),'win10', arch, 'MBR', createViewer)
    app.init()
    app.run()

if __name__ == "__main__":
    main(sys.argv)