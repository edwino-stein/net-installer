from subprocess import call
import requests

class Application(object):
    
    app = None
    viewer = None

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

    def __init__(self, winTarget, arch, bootMode, createViewHandle):
        Application.app = self

        self.winTarget = winTarget
        self.archTarget = arch
        self.bootMode = bootMode
        self.viewer = createViewHandle()
    
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
        self.versionsWidget.bind('<<ComboboxSelected>>', Application.onSelectVerion);
        self.viewer.addCLickListener('refresh', Application.onClick)

        self.letterListWidget['values'] = [chr(i)+':' for i in range(65, 91)];
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
        if call(['ping', serverUri, '-n', '1' , '-w', '250']) != 0 :
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

    @staticmethod
    def onClick(id, viewer, event):

        if id == 'refresh':
            Application.app.refresh();

    @staticmethod
    def onSelectVerion(event):

        item = Application.app.versionsWidget.get()
        path = Application.app.availablePaths[item]['path']

        Application.app.installPathWidget['state'] = 'normal'
        Application.app.installPathWidget.delete(0, 'end')
        Application.app.installPathWidget.insert(0, path)
        Application.app.installPathWidget['state'] = 'readonly'

        Application.app.runWidget['state'] = 'normal'
        