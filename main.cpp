#include <QGuiApplication>
#include <QOpenGLContext>
#include <QOffscreenSurface>
#include <QDebug>

using namespace std;

int main(int argc, char** argv)
{
    QGuiApplication a(argc, argv);

//    QSurfaceFormat surfaceFormat;
//    surfaceFormat.setVersion(3, 2);
//    surfaceFormat.setProfile(QSurfaceFormat::NoProfile);
//    surfaceFormat.setDepthBufferSize(24);
//    surfaceFormat.setRedBufferSize(8);
//    surfaceFormat.setGreenBufferSize(8);
//    surfaceFormat.setBlueBufferSize(8);
//    surfaceFormat.setAlphaBufferSize(0);
//    surfaceFormat.setStencilBufferSize(0);
//    surfaceFormat.setSamples(0);
//    surfaceFormat.setSwapBehavior(QSurfaceFormat::DefaultSwapBehavior);
//    surfaceFormat.setSwapInterval(1);
//    surfaceFormat.setOptions(0);

//    qDebug() << "[surfaceFormat] " << surfaceFormat;
//    QOpenGLContext context;
//    context.setFormat(surfaceFormat);
//    qDebug() << "[context.isValid()] " << context.isValid();
//    qDebug() << "[context.format()] " << context.format();
//    qDebug() << "[context.create()] " << context.create();
//    qDebug() << "[context.format()] " << context.format();

    int gl_versions[][2] = {
        1, 0,
        1, 1,
        1, 2,
        1, 3,
        1, 4,
        1, 5,
        2, 0,
        2, 1,
        3, 0,
        3, 1,
        3, 2,
        3, 3,
        4, 0,
        4, 1,
        4, 2,
        4, 3,
        4, 4,
        4, 5,
        4, 6
    };

    //Test OpenGL Versions
    for(int i = 0; i < 19; i++)
    {
        QSurfaceFormat surfaceFormat;
        surfaceFormat.setVersion(gl_versions[i][0], gl_versions[i][1]);
        surfaceFormat.setProfile(QSurfaceFormat::CoreProfile);
        QOpenGLContext context;
        context.setFormat(surfaceFormat);
        if(context.create())
        {
            if(context.format().majorVersion() == gl_versions[i][0] && context.format().minorVersion() == gl_versions[i][1])
            {
                qDebug() << "OpenGL " << QString("%1.%2").arg(gl_versions[i][0]).arg(gl_versions[i][1]) << " Supported";
                QOffscreenSurface offscreenSurface;
                offscreenSurface.create();
                context.makeCurrent(&offscreenSurface);
                qDebug() << "GL_VENDOR: " << (char *)glGetString(GL_VENDOR);
                qDebug() << "GL_RENDERER: " << (char *)glGetString(GL_RENDERER);
                qDebug() << "GL_VERSION: " << (char *)glGetString(GL_VERSION);
                qDebug() << "GL_SHADING_LANGUAGE_VERSION: " << (char *)glGetString(GL_SHADING_LANGUAGE_VERSION);
                context.doneCurrent();
            }
            else
            {
                qDebug() << "OpenGL " << QString("%1.%2").arg(gl_versions[i][0]).arg(gl_versions[i][1]) << " Auto Translate to " << QString("%1.%2").arg(context.format().majorVersion()).arg(context.format().minorVersion());
            }
        }
        else
        {
            qDebug() << "OpenGL " << QString("%1.%2").arg(gl_versions[i][0]).arg(gl_versions[i][1]) << " Unsupported";
        }
        qDebug() << "---------------------------------------------------------------";
    }

    int es_versions[][2] = {
        1, 0,
        1, 1,
        2, 0,
        3, 0,
        3, 1,
        3, 2
    };

    //Test OpenGL ES Versions
    for(int i = 0; i < 6; i++)
    {
        QSurfaceFormat surfaceFormat;
        surfaceFormat.setVersion(es_versions[i][0], es_versions[i][1]);
        surfaceFormat.setProfile(QSurfaceFormat::CoreProfile);
        surfaceFormat.setRenderableType(QSurfaceFormat::OpenGLES);
        QOpenGLContext context;
        context.setFormat(surfaceFormat);
        if(context.create())
        {
            if(context.format().majorVersion() == es_versions[i][0] && context.format().minorVersion() == es_versions[i][1])
            {
                qDebug() << "OpenGL ES " << QString("%1.%2").arg(es_versions[i][0]).arg(es_versions[i][1]) << " Supported";
                QOffscreenSurface offscreenSurface;
                offscreenSurface.create();
                context.makeCurrent(&offscreenSurface);
                qDebug() << "GL_VENDOR: " << (char *)glGetString(GL_VENDOR);
                qDebug() << "GL_RENDERER: " << (char *)glGetString(GL_RENDERER);
                qDebug() << "GL_VERSION: " << (char *)glGetString(GL_VERSION);
                qDebug() << "GL_SHADING_LANGUAGE_VERSION: " << (char *)glGetString(GL_SHADING_LANGUAGE_VERSION);
                context.doneCurrent();
            }
            else
            {
                qDebug() << "OpenGL ES " << QString("%1.%2").arg(es_versions[i][0]).arg(es_versions[i][1]) << " Auto Translate to " << QString("%1.%2").arg(context.format().majorVersion()).arg(context.format().minorVersion());
            }
        }
        else
        {
            qDebug() << "OpenGL ES " << QString("%1.%2").arg(es_versions[i][0]).arg(es_versions[i][1]) << " Unsupported";
        }
        qDebug() << "---------------------------------------------------------------";
    }

    return 0;
}
