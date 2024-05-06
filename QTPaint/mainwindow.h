#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>

class AreaDeDibujo;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void abrir();
    void guardar();
    void colorDeLapiz();
    void penWidth();
    void usarBorrador(); // Nuevo slot para la función de borrador

private:
    void crearAcciones();
    void crearMenus();

    bool talvezSalvar();
    bool guardarArchivo(const QByteArray &formatoArchivo);

    AreaDeDibujo *pinImagen;

    QMenu *menuGuardarComo;
    QMenu *menuArchivo;
    QMenu *menuOpciones;

    QAction *accionAbrir;

    QList<QAction *> accionesGuardarComo;
    QAction *accionDeSalir;
    QAction *actColorLapiz;
    QAction *penWidthAct;
    QAction *actLimpiarPantalla;
    QAction *actBorrador;
};

#endif

