Informe Técnico
Proyecto en el framework QT – Aplicativo tipo ‘Paint’.

Integrantes del proyecto con sus respectivos códigos.
•	Carlos Eduardo Grisales Restrepo	1055750849
•	Maycol Becerra Castro			1221714653
•	David Stiven Rivas Obando		1004685578 
•	Pablo León Rueda			1123890964

Funcionamiento de la App.
La app consta de una carpeta que se divide en las siguientes sub carpetas:
1.	Headers donde se contienen las cabeceras ‘areadedibujo.h’ y ‘mainwindow.h’ 
2.	Sources donde están los archivos ‘.cpp’ tales como ‘main.cpp’, ‘areadedibujo.cpp’ y ‘mainwindow.cpp’ 
3.	Forms carpeta en la que se almacenan los archivos ‘.ui’.
En un proyecto de Qt en C++ la carpeta Forms es utilizada para almacenar los archivos de diseño de interfaz gráfica creados con el Editor de Formularios Qt Designer. Estos archivos suelen contener la descripción visual de la interfaz de usuario, incluyendo los widgets, su disposición, propiedades y señales asociadas.
4.	Y, por último, el archivo ‘.pro’. Es un archivo de configuración del proyecto. Se utiliza para especificar las dependencias, configuraciones de compilación, enlazado de bibliotecas y otros detalles importantes para compilar y construir un proyecto.
   
- Headers: 
Las cabeceras contienen las declaraciones de clases, funciones y variables que se utilizan en tu código. Proporcionan una interfaz para que otros archivos de código fuente puedan utilizar estas clases y funciones sin necesidad de conocer los detalles de su implementación. Las cabeceras son fundamentales para la modularidad y la reutilización de código en proyectos de C+
- Sources:
Los Sources contienen la implementación de las clases, funciones y variables declaradas en los archivos de cabecera (.h o .hpp). En esencia, los archivos de código fuente son donde escribes el código real para realizar las operaciones y definir el comportamiento de tu programa en un proyecto de C++.
- Código comentado con explicaciones:
- 
// ---------- mainwindow.h ----------
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList> // Libreria usada para la creación de la app.
#include <QMainWindow>

// Área para garabatear, donde se va a pintar.
class AreaDeDibujo;

class MainWindow : public QMainWindow
{
    // Declara nuestra clase como un objeto Qt, la cual
    // es la clase base para todos nuestros objetos de Qt
    // Los objetos de Qt se encargan de manejar eventos.

    Q_OBJECT

    /* Diferencia:
     * public: Accesible desde cualquier parte.
     * private: Solo accesible desde dentro de la clase.
     * protected: Accesible desde dentro de la clase y por clases derivadas.*/

public:
    MainWindow();

protected:
    // Funcion usada para terminar un evento, por ejemplo si el usuario trata de cerrar el programa sin guardar,
    // esto hace que no sea posible.


    void closeEvent(QCloseEvent *event) override;

// Los eventos que pueden suceder (desencadenarse) (se les llama Slots en Qt) / Metodos de la clase.
// Son solo prototipos que se "heredan" (incluyen) a mainwindow.cpp.
private slots:
    void abrir();   // Abrir imagenes.
    void guardar();
    void colorDeLapiz();
    void penWidth();//  Para cambiar el tamaño del lapiz.

private:
    // Vinculará las acciones del usuario a las funciones.
    void crearAcciones();
    void crearMenus();

    // Comprobará si se han producido cambios desde el último guardado.
    bool talvezSalvar();

    // Abre el dialogo de guardado y guarda el archivo.
    bool guardarArchivo(const QByteArray &formatoArchivo);

    // En donde se dibujara.
    AreaDeDibujo *pinImagen;

    // Menú de Widgets, de los que esta compuesta la aplicación.
    QMenu *menuGuardarComo;
    QMenu *menuArchivo;
    QMenu *menuOpciones;

    // Todas las acciones que pueden ocurrir.
    QAction *accionAbrir;

    /*  Acciones vinculadas a formatos de archivo específicos.
     *  QList es un contenedor de listas proporcionado por el framework Qt que contiene
     *  punteros a objetos QAction. Sugiere una lista de acciones relacionadas con guardar.
        Cada uno de los siguientes punteros corresponde a una accion especifica.*/
    QList<QAction *> accionesGuardarComo;
    QAction *accionDeSalir;
    QAction *actColorLapiz;
    QAction *penWidthAct;
    QAction *accionDeImprimir;
    QAction *actLimpiarPantalla;
};

#endif

// ---------- END mainwindow.h ----------
 
// ---------- areadedibujo.h ----------
 
#ifndef AREADEDIBUJO_H
#define AREADEDIBUJO_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
//talvezGuardar();

/* AreaDeDibujo hereda de la clase QWidget y obtiene todas las características y
 * funcionalidades de QWidget, por lo tanto puede actuar como un widget dentro de la App.
 * La clase QWidget es una clase base proporcionada por el framework Qt que representa una
 * ventana o widget en una interfaz gráfica de usuario (GUI).
 * */
class AreaDeDibujo : public QWidget
{
    /* Declara nuestra clase como un objeto Qt,
     * la cual es la clase base para todos nuestros objetos de Qt
     * Los objetos de Qt se encargan de manejar eventos.*/

    Q_OBJECT

public:
    AreaDeDibujo(QWidget *parent = 0); //crea el Área de dibujo

    // Metodos para manejar todos los elementos.
    bool abrirImagen(const QString &nombreArchivo);
    bool guardarImagen(const QString &nombreArchivo, const char *formatoArchivo);
    void establecerColorDeLapiz(const QColor &nuevoColor);
    void establecerTamañoDeLapiz(int nuevoTamaño);

    // Si la imagen ha sido modificada desde la ultima vez que se guardo.
    bool haSidoMoficada() const { return modificada; }
    QColor colorDeLapiz() const { return miColorDeLapiz; }
    int penWidth() const { return miTamañoDeLapiz; }

    /* Diferencia:
     * Public define la visibilidad de los miembros, public slot define
     * una función especial que puede ser invocada en respuesta a eventos o
     * señales dentro del framework Qt, aparte este es propio de Qt. */
public slots:

    // Eventos a manejar
    void limpiarImagen();
    void imprimir();

protected:
    //Eventos relacionados con el funcionamiento del mouse.
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;   //ver explicación en el documento.
    void mouseReleaseEvent(QMouseEvent *event) override;

    // Actualiza el area de dibujo en la que estamos pintando.
    void paintEvent(QPaintEvent *event) override;

    /* Se asegura de que el area en la que estamos dibujando se
     * mantenga del mismo tamaño del widget */
    void resizeEvent(QResizeEvent *event) override;

private:
    void trazarLinea(const QPoint &puntoFinal); // Para dibujar una linea, va desde el punto previo hasta el actual.
    void tamañoDeLaImagen(QImage *imagen, const QSize &tamañoNuevo);

    /* Este bool monitorea si la imagen fue modificada o no, dependiendo de si hemos
     * guardado despues de un cambio se marcara como verdadero o falso. */

    bool modificada;
    /* Este bool marcara verdadero o falso dependiendo de si
     * el usuario esta dibujando o no. */
    bool garabatos;

    // Mantienen el tamaño y color actuales del lapiz.
    int miTamañoDeLapiz;
    QColor miColorDeLapiz;

    // Almacena la imagen que se está dibujando.
    QImage imagen;

    // Almacena la ubicación actual del mouse.
    QPoint ultimoPunto;
};

#endif 
// ---------- END areadedibujo.h ----------
 
// ---------- main.cpp ----------
 
#include "mainwindow.h" // Incluye todo el arhivo de la cabecera mainwindow.h
#include <QApplication>

int main(int argc, char *argv[])
{
    // Aplicación principal.
    QApplication app(argc, argv);

    // Crea y abre una ventana
    MainWindow window;
    window.show();

    /* Muestra la venta principal, este retorno crea un bucle
     * infinito que muestra la aplicacion hasta que el usuario la cierre. */
    return app.exec();
} 
// ---------- END main.cpp ----------
 
// ---------- mainwindow.cpp ----------
 
#include <QtWidgets>

#include "mainwindow.h"
#include "areadedibujo.h"


// Constructor de MainWindow
/* El operador '::' Se utiliza para acceder a miembros de una clase,
 * variables estáticas y funciones miembro
 * dentro de una clase o espacio de nombres. Es como decir "dentro de esto". Por ejemplo, si tienes
 * una clase llamada "Persona" y quieres acceder a su
 * función miembro "saludar()", usarías:
 *  "Persona::saludar()" */
MainWindow::MainWindow()
{
    // Crea el widget AreaDeDibujo y conviértelo en el widget central.
    pinImagen = new AreaDeDibujo;
    setCentralWidget(pinImagen);

    // Crea acciones y menus
    crearAcciones();
    crearMenus();

    // Titulo del widget
    setWindowTitle(tr("Editor de dibujo"));

    // Tamaño de la app
    resize(600, 600);
}

// Si el usuario trata de cerrar la App.
void MainWindow::closeEvent(QCloseEvent *event)
{
    /*Si intentan cerrar, MaybeSave() devuelve verdadero,
     * si no se han realizado cambios y la aplicación se cierra */
    if (talvezSalvar()) {
        event->accept();
    } else {

        //Si no han habido cambios, se ignora el evento.
        /* El operador "->" en C++ se utiliza principalmente para acceder
         * a los miembros de un objeto a través de un puntero a dicho objeto; Ej:
         *  class Persona {
         *  public:
         *  void saludar() {
         *  cout << "¡Hola! Soy una persona." << endl;}
         *  };
         *  int main() {
         *  Persona p;
         *  Persona* ptr = &p;
         *  // Accediendo al miembro "saludar()" a través del puntero usando el operador "->"
         *  ptr->saludar();
         * */
        event->ignore();
    }
}

// Comprueba si la imagen actual ha sido cambiada y luego abre un cuadro de diálogo para abrir un archivo
void MainWindow::abrir()
{
    /* Si se intenta cerrar el programa, el bucle revisa si se hicierón cambios desde
     * la ultima vez que se guardo.
     * talvezSalvar() retorna verdadero si no se han hecho cambios y cierra el programa. */

    if (talvezSalvar()) {

        // Obtiene el archivo a abrir desde un cuadro de dialogo.
        // tr da el nombre a la opcion "abrir archivo".
        // QDir abre el directorio actual.
        QString nombreArchivo = QFileDialog::getOpenFileName(this,
                                                        tr("Abrir Archivo"), QDir::currentPath());
        if (!nombreArchivo.isEmpty())
            pinImagen->abrirImagen(nombreArchivo);
    }
}

// Se llama cuando el usuario hace clic en "Guardar como" en el menú.
void MainWindow::guardar()
{
    // una QAction representa la acción del usuario clicando.
    QAction *action = qobject_cast<QAction *>(sender());

    // Almacena el arreglo de bytes de los datos del usuario.
    QByteArray formatoArchivo = action->data().toByteArray();

    // Lo pasa para que se guarde.
    guardarArchivo(formatoArchivo);
}

// Abre un dialogo para cambiar el color del lápiz.
void MainWindow::colorDeLapiz()
{
    // Guarda el color elegido del dialogo
    QColor nuevoColor = QColorDialog::getColor(pinImagen->colorDeLapiz());

    // Si es un color válido, se configura como nuevo color
    if (nuevoColor.isValid())
        pinImagen->establecerColorDeLapiz(nuevoColor);
}

// Guarda el ancho elegido del dialogo
void MainWindow::penWidth()
{
    // Almacena el valor del botón
    bool ok;

    /* tr("Editor de dibujo") es el titulo.
     * El proximo tr es el texto a mostrar en pantalla.
     * Obtiene el ancho actual del lápiz.
     * Defina los botones de mínimo, máximo, step y ok. */
    int nuevoTamaño = QInputDialog::getInt(this, tr("Editor de dibujo"),
                                        tr("Selecciona el tamaño :"),
                                        pinImagen->penWidth(),
                                        1, 50, 1, &ok);
    // Cambia el tamaño del lápiz.
    if (ok)
        pinImagen->establecerTamañoDeLapiz(nuevoTamaño);
}

// Define acciones de menú que llaman a funciones
void MainWindow::crearAcciones()
{
    // Crea la acción vinculada al menú.
    accionAbrir = new QAction(tr("&Abrir..."), this);

    // Definir la tecla de acceso directo asociada a accionAbrir
    accionAbrir->setShortcuts(QKeySequence::Open);

    // Vincula la acción a MainWindow::open()
    connect(accionAbrir, SIGNAL(triggered()), this, SLOT(abrir()));
    /* Obtiene una lista de los formatos de archivo admitidos.
     *  QImageWriter se utiliza para pasar imágenes en archivos. */
    foreach (QByteArray format, QImageWriter::supportedImageFormats()) {
        QString text = tr("%1...").arg(QString(format).toUpper());

        // Crea una acción para cada formato de archivo.

        QAction *action = new QAction(text, this);

        // Establece una acción para cada formato de archivo.
        action->setData(format);

        // Cuando se clickee llamar a MainWindow::guardar()
        connect(action, SIGNAL(triggered()), this, SLOT(guardar()));

        /* Adjunte cada elemento del menú de opciones de formato de
         * archivo a "Guardar como" mediante el metodo .append */
        accionesGuardarComo.append(action);
    }

    // Crea una acción de salida y la vincula a MainWindow::close()
    accionDeSalir = new QAction(tr("&Salir"), this);
    accionDeSalir->setShortcuts(QKeySequence::Quit);
    connect(accionDeSalir, SIGNAL(triggered()), this, SLOT(close()));

    // Crea una acción para darle color al lápiz y la vincula a MainWindow::colorDeLapiz()
    actColorLapiz = new QAction(tr("&Color de lapiz..."), this);
    connect(actColorLapiz, SIGNAL(triggered()), this, SLOT(colorDeLapiz()));

    // Crea una acción para darle tamaño al lápiz y la vincula a MainWindow::penWidth()
    penWidthAct = new QAction(tr("&Tamaño de lapiz..."), this);
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));

    // Crea una acción para limpiar la pantalla y la vincula a MainWindow::limpiarImagen()
    actLimpiarPantalla = new QAction(tr("&Limpiar pantalla"), this);
    actLimpiarPantalla->setShortcut(tr("Ctrl+L"));
    connect(actLimpiarPantalla, SIGNAL(triggered()),
            pinImagen, SLOT(limpiarImagen()));
}

// Crea nuestra barra de menus.
void MainWindow::crearMenus()
{
    // Crea una opcción para "Guardar como" y el listado de tipos de archivo.
    menuGuardarComo = new QMenu(tr("&Guardar como: "), this);
    foreach (QAction *action, accionesGuardarComo)
        menuGuardarComo->addAction(action);

    // Adjunta todas las acciones al archivo.
    menuArchivo = new QMenu(tr("&Archivo"), this);
    menuArchivo->addAction(accionAbrir);
    menuArchivo->addMenu(menuGuardarComo);
    menuArchivo->addSeparator();
    menuArchivo->addAction(accionDeSalir);

    // Adjunta todas las acciones a opciones.
    menuOpciones = new QMenu(tr("&Opciones"), this);
    menuOpciones->addAction(actColorLapiz);
    menuOpciones->addAction(penWidthAct);
    menuOpciones->addSeparator();
    menuOpciones->addAction(actLimpiarPantalla);

    // Agrega los items del menu a la barra del menú.
    menuBar()->addMenu(menuArchivo);
    menuBar()->addMenu(menuOpciones);
}

bool MainWindow::talvezSalvar()
{
    // Para vereficar por cambios desde la ultima vez que se guardo.
    if (pinImagen->haSidoMoficada()) {
        QMessageBox::StandardButton ret;

        ret = QMessageBox::warning(this, tr("Editor de dibujo"),
                                   tr("La imagen ha sido modificada.\n"
                                      "¿Quieres guardar los cambios?"), // Añade texto a cada botón.
                                   QMessageBox::Save | QMessageBox::Discard
                                       | QMessageBox::Cancel);

        // Si se hace clic en el botón 'Guardar', se solicita que se guarde el archivo
        if (ret == QMessageBox::Save) {
            return guardarArchivo("png");

            // Si se cancela no se hace nada.
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

/* El metodo bool guardarArchivo se invoca cuando el usuario quiere cerrar
 * el programa sin guardar el dibujo en el que ha trabajado, su funcionalidad es evitar
 * que esto pase. */

bool MainWindow::guardarArchivo(const QByteArray &formatoArchivo)
{
    //Define ruta, nombre y tipo de archivo predeterminado
    QString initialPath = QDir::currentPath() + "/untitled." + formatoArchivo;

    /* Obtiene el archivo seleccionado del diálogo,
     * y agregua el formatos y extension al archivo adecuados. */
    QString nombreArchivo = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                    initialPath,
                                                    tr("%1 Files (*.%2);;All Files (*)")
                                                        .arg(QString::fromLatin1(formatoArchivo.toUpper()))
                                                        .arg(QString::fromLatin1(formatoArchivo)));

    // Si nombreArchivo esta vacio, retorna falso y se hace nada.
    if (nombreArchivo.isEmpty()) {
        return false;
    } else {

        /* Si lo anterior no pasa, llama al metodo guardarImagen y le pasa los
         * respectivos parametros para que este se ejecute. */
        return pinImagen->guardarImagen(nombreArchivo, formatoArchivo.constData());
    }
} 
// ---------- END mainwindow.cpp ----------
 
// ---------- areadedibujo.cpp ----------
 #include <QtWidgets>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif

#include "areadedibujo.h"

//Constructor.
AreaDeDibujo::AreaDeDibujo(QWidget *parent)
    : QWidget(parent)
{
    // Arraiga el widget en la parte superior izquierda incluso si se cambia de tamaño.
    setAttribute(Qt::WA_StaticContents);

    // Establecer valores predeterminados para las variables.
    modificada = false;
    garabatos = false;
    miTamañoDeLapiz = 1;
    miColorDeLapiz = Qt::blue;
}

// Metodo usado para abrir/cargar la imagen y ponerla en el widget
bool AreaDeDibujo::abrirImagen(const QString &nombreArchivo)
{
    // Mantiene la imagen.
    QImage imagenCargada;

    // Si la imagen no fue cargada, dejar esta función.
    if (!imagenCargada.load(nombreArchivo))
        return false;

    QSize tamañoNuevo = imagenCargada.size().expandedTo(size());
    tamañoDeLaImagen(&imagenCargada, tamañoNuevo);
    imagen = imagenCargada;
    modificada = false;
    update();
    return true;
}

// Metodo usaddo para guardar la Imagen
bool AreaDeDibujo::guardarImagen(const QString &nombreArchivo, const char *formatoArchivo)
{
    //Para mantener la imagen.
    QImage imagenVisible = imagen;
    tamañoDeLaImagen(&imagenVisible, size());

    if (imagenVisible.save(nombreArchivo, formatoArchivo)) {
        modificada = false;
        return true;
    } else {
        return false;
    }
}

//Metodo usado para cambiar el color del lápiz.
void AreaDeDibujo::establecerColorDeLapiz(const QColor &nuevoColor)
{
    miColorDeLapiz = nuevoColor;
}

//Metodo usado par acambiar el tamaño del Lapiz
void AreaDeDibujo::establecerTamañoDeLapiz(int nuevoTamaño)
{
    miTamañoDeLapiz = nuevoTamaño;
}

//Metodo usado para rellenar todo el espacio de blanco.
void AreaDeDibujo::limpiarImagen()
{
    //rellena la imagen con el metodo fill y el color blanco cullo código RGB es 255, 255, 255.
    imagen.fill(qRgb(255, 255, 255));
    modificada = true;
    update();
}

// If a mouse button is pressed check if it was the
// left button and if so store the current position
// Set that we are currently drawing
void AreaDeDibujo::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        ultimoPunto = event->pos();
        garabatos = true;
    }
}

// When the mouse moves if the left button is clicked
// we call the drawline function which draws a line
// from the last position to the current
void AreaDeDibujo::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && garabatos)
        trazarLinea(event->pos());
}

// If the button is released we set variables to stop drawing
void AreaDeDibujo::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && garabatos) {
        trazarLinea(event->pos());
        garabatos = false;
    }
}

// QPainter provides functions to draw on the widget
// The QPaintEvent is sent to widgets that need to
// update themselves
void AreaDeDibujo::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // Returns the rectangle that needs to be updated
    QRect dirtyRect = event->rect();

    // Draws the rectangle where the image needs to
    // be updated
    painter.drawImage(dirtyRect, imagen, dirtyRect);
}

// Resize the image to slightly larger then the main window
// to cut down on the need to resize the image
void AreaDeDibujo::resizeEvent(QResizeEvent *event)
{
    if (width() > imagen.width() || height() > imagen.height()) {
        int nuevoTamaño = qMax(width() + 128, imagen.width());
        int newHeight = qMax(height() + 128, imagen.height());
        tamañoDeLaImagen(&imagen, QSize(nuevoTamaño, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void AreaDeDibujo::trazarLinea(const QPoint &puntoFinal)
{
    // Used to draw on the widget
    QPainter painter(&imagen);

    // Set the current settings for the pen
    painter.setPen(QPen(miColorDeLapiz, miTamañoDeLapiz, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));

    // Draw a line from the last registered point to the current
    painter.drawLine(ultimoPunto, puntoFinal);

    // Set that the image hasn't been saved
    modificada = true;

    int rad = (miTamañoDeLapiz / 2) + 2;

    // Call to update the rectangular space where we drew
    update(QRect(ultimoPunto, puntoFinal).normalized()
               .adjusted(-rad, -rad, +rad, +rad));

    // Update the last position where we left off drawing
    ultimoPunto = puntoFinal;
}

// When the app is resized create a new image using
// the changes made to the image
void AreaDeDibujo::tamañoDeLaImagen(QImage *imagen, const QSize &tamañoNuevo)
{
    // Check if we need to redraw the image
    if (imagen->size() == tamañoNuevo)
        return;

    // Create a new image to display and fill it with white
    QImage newImage(tamañoNuevo, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));

    // Draw the image
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *imagen);
    *imagen = newImage;
}

// Print the image
void AreaDeDibujo::imprimir()
{
    // Check for print dialog availability
#if QT_CONFIG(printdialog)

    // Can be used to print
    QPrinter printer(QPrinter::HighResolution);

    // Open printer dialog and print if asked
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = imagen.size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(imagen.rect());
        painter.drawImage(0, 0, imagen);
    }
#endif // QT_CONFIG(printdialog)
}
 
// ---------- END scribblearea.cpp ----------

