#include <QImage>
#include <QPixmap>
#include <QtAlgorithms>
#include "webvfx/image.h"
#include "webvfx/parameters.h"
#include "webvfx/web_page.h"
#include "webvfx/web_script.h"

namespace WebVFX
{

WebScript::WebScript(WebPage* parent, Parameters* parameters)
    : QObject(parent)
    , parameters(parameters)
{
}

WebScript::~WebScript()
{
    delete parameters;
    // Delete all images in map
    qDeleteAll(imageMap);
}

void WebScript::render(double time)
{
    emit renderRequested(time);
}

Image WebScript::getImage(const QString& name, const QSize& size)
{
    QImage* image = imageMap.value(name);
    if (!image || image->size() != size) {
        delete image;
        image = new QImage(size, QImage::Format_RGB888);
        imageMap.insert(name, image);
    }
    return Image(image->bits(), image->width(), image->height(), image->byteCount());
}

double WebScript::getNumberParameter(const QString& name)
{
    if (parameters)
        return parameters->getNumberParameter(name.toStdString());
    else
        return 0;
}

const QString WebScript::getStringParameter(const QString& name)
{
    if (parameters)
        return QString::fromStdString(parameters->getStringParameter(name.toStdString()));
    else
        return QString();
}

// QtWebkit Bridge converts QImages to QPixmaps anyway,
// so better to do the conversion here since handing over a QImage
// would cause it's shared data to be duplicated the next time we wrote to it's bits.
// http://doc.qt.nokia.com/latest/qimage.html#bits
const QPixmap WebScript::getImage(const QString& name)
{
    QImage* image = imageMap.value(name);
    if (image)
        return QPixmap::fromImage(*image);
    else
        return QPixmap();
}

}
