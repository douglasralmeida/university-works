const electron = require('electron')
// Modulo para controla a aplicacao.
const app = electron.app
// Modulo para criar janela.
const BrowserWindow = electron.BrowserWindow

const path = require('path')
const url = require('url')

// Mantenha uma referencia globao a janela, do contrario a janela sera
// fechada automaticamente quando seu objeto for coletado pelo gestor de lixo
let mainWindow

function createWindow () {
  // Criar a janela
  mainWindow = new BrowserWindow({width: 800, height: 600, icon: __dirname + '/resources/appicon.png'});
  mainWindow.setMenuBarVisibility(false);

  // e carregar o arquivo index.html da aplicacao.
  mainWindow.loadURL(url.format({
    pathname: path.join(__dirname, 'index.html'),
    protocol: 'file:',
    slashes: true
  }))

  mainWindow.webContents.openDevTools();

  // Evento quando a a janela for fechada
  mainWindow.on('closed', function () {
    mainWindow = null
  })
}

// Evento quando o Electron finalizar sua inicializacao
app.on('ready', createWindow);

// Encerrar aplicacao quando todas as janelas forem fechadas.
app.on('window-all-closed', function () {
  if (process.platform !== 'darwin') {
    app.quit()
  }
})

app.on('activate', function () {
  if (mainWindow === null) {
    createWindow()
  }
})