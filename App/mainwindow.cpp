#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "FrmUpdater/FrmUpdater.h"
#include "DlgAbout/DlgAbout.h"

#include "FrmViewer.h"
#include "ConnectThread.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    CFrmUpdater updater;
    ui->actionUpdate_U->setIcon(updater.windowIcon());
    
    m_pView = new QScrollArea(this);
    m_pView->setAlignment(Qt::AlignCenter);
    m_pView->setBackgroundRole(QPalette::Dark);
    CFrmViewer* pView = new CFrmViewer();
    m_pView->setWidget(pView);
    this->setCentralWidget(m_pView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_A_triggered()
{
    CDlgAbout about(this);
    about.m_AppIcon = QImage(":/image/App");
    if(about.isHidden())
#if defined (Q_OS_ANDROID)
        about.showMaximized();
#endif
        about.exec();    
}

void MainWindow::on_actionUpdate_U_triggered()
{
    CFrmUpdater* m_pfrmUpdater = new CFrmUpdater();
    m_pfrmUpdater->SetTitle(QImage(":/image/App"));
    m_pfrmUpdater->SetInstallAutoStartup();
#if defined (Q_OS_ANDROID)
    m_pfrmUpdater->showMaximized();
#else
    m_pfrmUpdater->show();
#endif   
}

void MainWindow::on_actionStatusBar_S_triggered()
{
    ui->statusbar->setVisible(!ui->statusbar->isVisible());
    ui->actionStatusBar_S->setChecked(ui->statusbar->isVisible());
}

void MainWindow::on_actionToolBar_T_triggered()
{
    ui->toolBar->setVisible(!ui->toolBar->isVisible());
    ui->actionToolBar_T->setChecked(ui->toolBar->isVisible());
}

void MainWindow::on_actionFull_screen_F_triggered()
{
    if(this->isFullScreen())
    {
        this->showNormal();
        ui->actionFull_screen_F->setIcon(QIcon(":/image/FullScreen"));
        ui->actionFull_screen_F->setText(tr("Full screen(&F)"));
        ui->actionFull_screen_F->setToolTip(tr("Full screen"));
        ui->actionFull_screen_F->setStatusTip(tr("Full screen"));
        ui->actionFull_screen_F->setWhatsThis(tr("Full screen"));
        
        ui->toolBar->setAllowedAreas(Qt::AllToolBarAreas);
        ui->toolBar->setVisible(ui->actionToolBar_T->isChecked());
        
        ui->statusbar->setVisible(ui->actionStatusBar_S->isChecked());
        ui->menubar->setVisible(true);
        return;
    }
    
    this->showFullScreen();
    ui->actionFull_screen_F->setIcon(QIcon(":/image/ExitFullScreen"));
    ui->actionFull_screen_F->setText(tr("Exit full screen(&E)"));
    ui->actionFull_screen_F->setToolTip(tr("Exit full screen"));
    ui->actionFull_screen_F->setStatusTip(tr("Exit full screen"));
    ui->actionFull_screen_F->setWhatsThis(tr("Exit full screen"));
        
    ui->toolBar->setVisible(true);
    ui->toolBar->setAllowedAreas(Qt::NoToolBarArea);
        
    ui->statusbar->setVisible(false);
    ui->menubar->setVisible(false);
}

void MainWindow::on_actionOriginal_O_triggered()
{
}

void MainWindow::on_actionZoom_Z_triggered()
{
}

void MainWindow::on_actionKeep_AspectRation_K_triggered()
{
}

void MainWindow::on_actionExit_E_triggered()
{
    qApp->exit();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Escape:
        if(isFullScreen())
            on_actionFull_screen_F_triggered();
        break;
    }
}

void MainWindow::on_actionConnect_C_triggered()
{
    //TODO: 暂时测试用
    CConnectThread* pThread = new CConnectThread(
                dynamic_cast<CFrmViewer*>(m_pView->widget()));
    pThread->start();
}

void MainWindow::on_actionDisconnect_D_triggered()
{
    //TODO:
    CFrmViewer* pV = dynamic_cast<CFrmViewer*>(m_pView->widget());
    if(pV)
        pV->slotDisconnect();
}