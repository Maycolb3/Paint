#include <QtWidgets>

#include "mainwindow.h"
#include "areadedibujo.h"
// MainWindow constructor
MainWindow::MainWindow()
{
    pinImagen = new AreaDeDibujo;
    setCentralWidget(pinImagen);

    crearAcciones();
    crearMenus();

    setWindowTitle(tr("Editor de dibujo"));
    resize(800, 600);

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (talvezSalvar()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::abrir()
{
    if (talvezSalvar()) {
        QString nombreArchivo = QFileDialog::getOpenFileName(this,
                                                             tr("Abrir Archivo"), QDir::currentPath());
        if (!nombreArchivo.isEmpty())
            pinImagen->abrirImagen(nombreArchivo);
    }
}

void MainWindow::guardar()
{
    QAction *action = qobject_cast<QAction *>(sender());

    QByteArray formatoArchivo = action->data().toByteArray();

    guardarArchivo(formatoArchivo);
}

void MainWindow::colorDeLapiz()
{
    QStringList coloresBasicos;
    coloresBasicos << "Blanco" << "Negro" << "Rojo" << "Azul" << "Amarillo" << "Verde" << "Naranja";

    bool ok;
    QString colorSeleccionado = QInputDialog::getItem(this, tr("Seleccionar Color"),
                                                      tr("Color:"), coloresBasicos, 0, false, &ok);
    if (ok) {
        QColor nuevoColor;
        if (colorSeleccionado == "Blanco") {
            nuevoColor = Qt::white;
        } else if (colorSeleccionado == "Negro") {
            nuevoColor = Qt::black;
        } else if (colorSeleccionado == "Rojo") {
            nuevoColor = Qt::red;
        } else if (colorSeleccionado == "Azul") {
            nuevoColor = Qt::blue;
        } else if (colorSeleccionado == "Amarillo") {
            nuevoColor = Qt::yellow;
        } else if (colorSeleccionado == "Verde") {
            nuevoColor = Qt::green;
        } else if (colorSeleccionado == "Naranja") {
            nuevoColor = QColor(255, 140, 0); // Naranja
        }

        pinImagen->establecerColorDeLapiz(nuevoColor);
    }
}

void MainWindow::penWidth()
{
    bool ok;
    int nuevoTamaño = QInputDialog::getInt(this, tr("Editor de dibujo"),
                                           tr("Selecciona el tamaño :"),
                                           pinImagen->penWidth(),
                                           1, 250, 1, &ok);
    if (ok)
        pinImagen->establecerTamañoDeLapiz(nuevoTamaño);
}

void MainWindow::crearAcciones()
{
    accionAbrir = new QAction(tr("&Abrir..."), this);
    accionAbrir->setShortcuts(QKeySequence::Open);

    connect(accionAbrir, SIGNAL(triggered()), this, SLOT(abrir()));

    QStringList formatosPermitidos;
    formatosPermitidos<< "PNG" <<"JPG"<< "TIFF"<< "BMP" << "GIF";

    foreach (const QString &formato, formatosPermitidos) {
        QString text = tr("%1...").arg(formato);
        QAction *action = new QAction(text, this);

        action->setData(QByteArray(formato.toLatin1()));
        connect(action, SIGNAL(triggered()), this, SLOT(guardar()));

        accionesGuardarComo.append(action);
    }

    ;
    accionDeSalir = new QAction(tr("&Salir"), this);
    accionDeSalir->setShortcuts(QKeySequence::Quit);
    connect(accionDeSalir, SIGNAL(triggered()), this, SLOT(close()));

    actColorLapiz = new QAction(tr("&Color de lapiz..."), this);
    connect(actColorLapiz, SIGNAL(triggered()), this, SLOT(colorDeLapiz()));

    penWidthAct = new QAction(tr("&Tamaño de lapiz..."), this);
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));

    actLimpiarPantalla = new QAction(tr("&Limpiar pantalla"), this);
    actLimpiarPantalla->setShortcut(tr("Ctrl+L"));
    connect(actLimpiarPantalla, SIGNAL(triggered()),
            pinImagen, SLOT(limpiarImagen()));

    actBorrador = new QAction(tr("&Borrador"), this);
    actBorrador->setShortcut(tr("Ctrl+B"));
    connect(actBorrador, SIGNAL(triggered()), this, SLOT(usarBorrador()));
}

void MainWindow::crearMenus()
{
    menuGuardarComo = new QMenu(tr("&Guardar como: "), this);

    foreach (QAction *action, accionesGuardarComo)
        menuGuardarComo->addAction(action);

    menuArchivo = new QMenu(tr("&Archivo"), this);
    menuArchivo->addAction(accionAbrir);
    menuArchivo->addMenu(menuGuardarComo);
    menuArchivo->addSeparator();
    menuArchivo->addAction(accionDeSalir);

    menuOpciones = new QMenu(tr("&Opciones"), this);
    menuOpciones->addAction(actColorLapiz);
    menuOpciones->addAction(penWidthAct);
    menuOpciones->addSeparator();
    menuOpciones->addAction(actLimpiarPantalla);
    menuOpciones->addAction(actBorrador);

    menuBar()->addMenu(menuArchivo);
    menuBar()->addMenu(menuOpciones);

}

void MainWindow::usarBorrador()
{
    pinImagen->establecerColorDeLapiz(Qt::white);
}

bool MainWindow::talvezSalvar()
{
    if (pinImagen->haSidoMoficada()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Editor de dibujo"),
                                   tr("La imagen ha sido modificada.\n"
                                      "¿Quieres guardar los cambios?"),
                                   QMessageBox::Save | QMessageBox::Discard
                                       | QMessageBox::Cancel);
        if (ret == QMessageBox::Save) {
            return guardarArchivo("png");
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

bool MainWindow::guardarArchivo(const QByteArray &formatoArchivo)
{
    QString initialPath = QDir::currentPath() + "/Sin titulo." + formatoArchivo;
    QString nombreArchivo = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                         initialPath,
                                                         tr("%1 Files (*.%2);;All Files (*)")
                                                             .arg(QString::fromLatin1(formatoArchivo.toUpper()))
                                                             .arg(QString::fromLatin1(formatoArchivo)));
    if (nombreArchivo.isEmpty()) {
        return false;
    } else {
        return pinImagen->guardarImagen(nombreArchivo, formatoArchivo.constData());
    }
}
