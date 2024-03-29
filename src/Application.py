from subprocess import call
from tkinter import filedialog
import subprocess
import requests
import os
import platform

class Application(object):
    
    app = None
    viewer = None
    smbUser = ('user', 'password')

    serverUrlWidget = None
    versionsWidget = None
    installPathWidget = None
    runWidget = None
    networkStatusWidget = None
    letterListWidget = None
    bootModeWidget = None
    archWidget = None

    winTarget = ''
    archTarget = ''
    bootMode = ''

    jsonConfig = 'netinstall.json'

    availablePaths = {}

    def __init__(self, smbUser, winTarget, createViewHandle, args):

        Application.app = self

        dScaling = 0
        isDBoot = False

        for i in args:

            if "dboot=" in i:
                isDBoot = i.split("=")[1] == "1"
                continue

            if "dscaling=" in i:
                dScaling = float(i.split("=")[1]);
                continue

        self.bootMode = self.getBootType(isDBoot)

        arch = platform.architecture()[0]
        if arch == '64bit':
            self.archTarget = 'x64'
        elif arch == '32bit':
            self.archTarget = 'x86'
        else:
            self.archTarget = 'Desconhecida'

        self.smbUser = smbUser
        self.winTarget = winTarget
        self.viewer = createViewHandle(dScaling)
    
    def init(self):

        self.serverUrlWidget = self.viewer.getWidgetById('serverUrl')
        self.versionsWidget = self.viewer.getWidgetById('version-list')
        self.installPathWidget = self.viewer.getWidgetById('install-path')
        self.runWidget = self.viewer.getWidgetById('run')
        self.networkStatusWidget = self.viewer.getWidgetById('network-status')
        self.letterListWidget = self.viewer.getWidgetById('letter-list')
        self.bootModeWidget = self.viewer.getWidgetById('boot-mode')
        self.archWidget = self.viewer.getWidgetById('arch')

        self.runWidget['state'] = 'disabled'
        self.viewer.addCLickListener('run', Application.onClick)
        self.viewer.addCLickListener('load-driver', Application.onClick)
        self.viewer.addCLickListener('run-diskpart', Application.onClick)
        self.viewer.addCLickListener('run-cmd', Application.onClick)

        self.versionsWidget.bind('<<ComboboxSelected>>', Application.onSelectVerion);
        self.viewer.addCLickListener('refresh', Application.onClick)

        letters = []
        for l in range(ord('A'), ord('Z') + 1):
            l = chr(l)+':'
            if not self.letterIsUsed(l):
                letters.append(l)
    
        self.letterListWidget['values'] = letters
        self.letterListWidget.set(self.letterListWidget['values'][0])

        self.bootModeWidget['text'] = self.bootMode
        self.archWidget['text'] = self.archTarget


    def run(self):
        self.refresh()
        self.viewer.loop()

    def onDetectNetWork(self):
        self.networkStatusWidget['text'] = 'Conectado'
        print('* Conexão detectada!')

    def refresh(self):
        
        self.availablePaths = {}
        self.versionsWidget['values'] = ()
        serverUri = self.serverUrlWidget.get()

        print('* Verificando ping com "'+serverUri+'"...')
        if Application.runProg(['ping', serverUri, '-n', '1' , '-w', '250'], False) != 0 :
            print('* Sem conxeão!')
            return
    	
        print('\n* Baixando arquivo json em "http://'+serverUri+'/'+ self.jsonConfig +'"...')
        
        response = requests.get('http://' + serverUri + '/' + self.jsonConfig)
        if response.status_code != 200:
            print('* Erro ao baixar o arquivo "'+self.jsonConfig+'".')
            print('* Codigo http: ' + str(response.status_code) + '.')
            return

        cfg = response.json();
        if self.winTarget not in cfg:
            print('* Erro ao buscar a versão alvo para o windows "' + self.winTarget + '".')
            return

        
        self.onDetectNetWork()
        print('* Versões disponíveis:')

        listValues = ()
        for i in cfg[self.winTarget]:

            item = self.winTarget+'-'+i
            i = cfg[self.winTarget][i]
            
            if self.archTarget not in i:
                continue
            
            listValues = listValues + (item,)

            self.availablePaths[item] = {
                'path': i[self.archTarget]['path'],
                'exec': i[self.archTarget]['exec']
            }

            print('\t- ' + item)
        
        if len(listValues) > 1 :
            self.versionsWidget['values'] = listValues
            self.versionsWidget.set(listValues[0])
            Application.onSelectVerion(None)
        else:
            print('\t - Nenhuma versão disponível')

    def onRunBtnClick(self):
        
        letter = self.letterListWidget.get();
        serverUri = self.serverUrlWidget.get();
        path = self.installPathWidget.get();
        item = Application.app.versionsWidget.get()
        exe = Application.app.availablePaths[item]['exec']

        if self.letterIsUsed(letter):
            if not os.path.isfile(letter + '\\'+ exe):
                print('* A letra de unidade "' + letter + '" já está em uso. Tente uma outra.')
        else:
            if not self.mountShared(letter, serverUri, path, self.smbUser):
                return

        Application.runProg([letter + '\\' + exe], True)

    def mountShared(self, letter, serverUri, path, user):

        url = '\\\\'+serverUri+'\\'+path

        print('* Tentando montar "'+url+'" em '+letter+'...')
        code = Application.runProg(['net', 'use', letter, url, '/u:'+user[0], user[1]], False)
        if code != 0:
            print('* Erro ao tentar montar unidade de rede.')
            print('* Codigo de erro: ' + str(code) + '.')
            return False

        print('* Unidade montada com sucesso!')
        return True

    def letterIsUsed(self, letter):
        return os.path.isdir(letter)

    def onLoadDriverBtnClick(self):

        driverFile = filedialog.askopenfilename(title = "Selecione o arquivo de driver...", filetypes = (("Driver .inf","*.inf"), ("all files","*.*")))

        if not driverFile:
            return

        print('* Carregando arquivo de driver "'+driverFile+'"...')
        code = Application.runProg(['drvload', driverFile], False)

        if code != 0:
            print('* Erro ao carregar driver com código '+ str(code) +'.')
        else:
            print("* Driver carregado com sucesso!")
            self.refresh()

    @staticmethod
    def onClick(id, viewer, event):

        if id == 'refresh':
            Application.app.refresh()

        if id == 'run':
            Application.app.onRunBtnClick()
    
        if id == 'load-driver':
            Application.app.onLoadDriverBtnClick()

        if id == 'run-diskpart':
            Application.runProg(['start.bat', 'diskpart'], True)

        if id == 'run-cmd':
            Application.runProg(['start.bat', 'cmd'], True)

    @staticmethod
    def onSelectVerion(event):

        item = Application.app.versionsWidget.get()
        path = Application.app.availablePaths[item]['path']

        Application.app.installPathWidget['state'] = 'normal'
        Application.app.installPathWidget.delete(0, 'end')
        Application.app.installPathWidget.insert(0, path)
        Application.app.installPathWidget['state'] = 'readonly'

        Application.app.runWidget['state'] = 'normal'
    
    @staticmethod
    def runProg(entry, independent):
        if independent:
            return subprocess.Popen(entry)
        else:
            return call(entry)

    @staticmethod
    def getBootType(isDebug):

        if isDebug :
            return "DEBUG"

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
        