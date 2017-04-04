#ifndef DISPLAY_H
#define DISPLAY_H

#include <QOpenGLFunctions_3_2_Core>
#include <QOpenGLWidget>

class IRenderer;

class Display : public QOpenGLWidget, protected QOpenGLFunctions_3_2_Core
{
    Q_OBJECT
public:
    explicit Display(QWidget *parent = 0);

    void setViewPort(const QRectF &viewPort);
    void setRenderer(IRenderer *renderer);


signals:

public slots:

    // QOpenGLWidget interface
protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;

private:
    QRectF mViewPort;
    IRenderer *mRenderer;


};

#endif // DISPLAY_H
