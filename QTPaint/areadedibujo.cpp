 #include <QtWidgets>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif

#include "areadedibujo.h"

AreaDeDibujo::AreaDeDibujo(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);

    modificada = false;
    garabatos = false;
    miTamañoDeLapiz = 1;
    miColorDeLapiz = Qt::blue;
}

bool AreaDeDibujo::abrirImagen(const QString &nombreArchivo)
{
    QImage imagenCargada;

    if (!imagenCargada.load(nombreArchivo))
        return false;

    QSize tamañoNuevo = imagenCargada.size().expandedTo(size());
    tamañoDeLaImagen(&imagenCargada, tamañoNuevo);
    imagen = imagenCargada;
    modificada = false;
    update();
    return true;
}

bool AreaDeDibujo::guardarImagen(const QString &nombreArchivo, const char *formatoArchivo)
{
    QImage imagenVisible = imagen;
    tamañoDeLaImagen(&imagenVisible, size());

    if (imagenVisible.save(nombreArchivo, formatoArchivo)) {
        modificada = false;
        return true;
    } else {
        return false;
    }
}

void AreaDeDibujo::establecerColorDeLapiz(const QColor &nuevoColor)
{
    miColorDeLapiz = nuevoColor;
}

void AreaDeDibujo::establecerTamañoDeLapiz(int nuevoTamaño)
{
    miTamañoDeLapiz = nuevoTamaño;
}

void AreaDeDibujo::limpiarImagen()
{
    imagen.fill(qRgb(255, 255, 255));
    modificada = true;
    update();
}

void AreaDeDibujo::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        ultimoPunto = event->pos();
        garabatos = true;
    }
}

void AreaDeDibujo::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && garabatos)
        trazarLinea(event->pos());
}

void AreaDeDibujo::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && garabatos) {
        trazarLinea(event->pos());
        garabatos = false;
    }
}

void AreaDeDibujo::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, imagen, dirtyRect);
}

void AreaDeDibujo::usarBorrador()
{
    // Obtener el color de fondo del lienzo
    QColor colorFondo = palette().color(backgroundRole());

    // Establecer el color del lápiz como el color de fondo
    establecerColorDeLapiz(colorFondo);
}

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
    QPainter painter(&imagen);

    painter.setPen(QPen(miColorDeLapiz, miTamañoDeLapiz, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));

    painter.drawLine(ultimoPunto, puntoFinal);
    modificada = true;

    int rad = (miTamañoDeLapiz / 2) + 2;

    update(QRect(ultimoPunto, puntoFinal).normalized()
               .adjusted(-rad, -rad, +rad, +rad));

    ultimoPunto = puntoFinal;
}

void AreaDeDibujo::tamañoDeLaImagen(QImage *imagen, const QSize &tamañoNuevo)
{
    if (imagen->size() == tamañoNuevo)
        return;

    QImage newImage(tamañoNuevo, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));

    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *imagen);
    *imagen = newImage;
}
