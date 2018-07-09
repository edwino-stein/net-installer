import sys
import platform
import subprocess
from GUI import createViewer
from Application import Application

def getBootType():

    output = subprocess.check_output(['boot-mode.bat'])
    if output == None :
        return 'Desconhecido'
    
    bootTypeCode = str(output).split(' ')[-1].split('\\r')[0];

    if bootTypeCode == '0x1':
        return 'BIOS'
    elif bootTypeCode == '0x2':
        return 'UEFI'
    else:
        return 'Desconhecido'



def main(argv):
    
    bootMode = getBootType()

    arch = platform.architecture()[0]
    if arch == '64bit':
        arch = 'x64'
    elif arch == '32bit':
        arch = 'x86'
    else:
        arch = 'Desconhecida'

    app = Application(('pxe', 'gwh28dgcmp'), 'win10', arch, bootMode, createViewer)
    app.init()
    app.run()

if __name__ == "__main__":
    main(sys.argv)