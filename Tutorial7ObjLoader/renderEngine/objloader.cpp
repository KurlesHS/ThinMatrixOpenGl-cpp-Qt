#include "objloader.h"

#include <QFile>
#include <QDebug>
#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QStringList>

ObjLoader::ObjLoader()
{

}

RawModelSharedPtr ObjLoader::loadObjModel(const QString &fileName, Loader *loader)
{
    RawModelSharedPtr result;
    QFile f(fileName);
    if (f.open(QIODevice::ReadOnly)) {
        QList<QVector3D> vertices;
        QList<QVector3D> normals;
        QList<QVector2D> textures;
        QList<GLint> indices;

        QVector<GLfloat> verticesArray;
        QVector<GLfloat> normalsArray;
        QVector<GLfloat> texturesArray;
        QVector<GLint> indicesArray;

        auto getVector3 = [](const QStringList line) {
            return QVector3D(line.at(1).toFloat(),
                             line.at(2).toFloat(),
                             line.at(3).toFloat());
        };

        auto getVector2 = [](const QStringList line) {
            return QVector2D(line.at(1).toFloat(),
                             line.at(2).toFloat());
        };

        bool arraysIsCreated = false;

        while (!f.atEnd()) {
            QString line = QString::fromLatin1(f.readLine());
            QStringList currentLine = line.split(" ");
            if (line.startsWith("v ") && currentLine.size() >= 4) {
                /* vertex positions */
                vertices.append(getVector3(currentLine));
            } else if (line.startsWith("vt ")) {
                /* textures coordinates */
                textures.append(getVector2(currentLine));
            } else if (line.startsWith("vn ")) {
                /* normals */
                normals.append(getVector3(currentLine));
            } else if (line.startsWith("f ")) {
                /* indexes */
                if (!arraysIsCreated) {
                    texturesArray.resize(vertices.size() * 2);
                    normalsArray.resize(vertices.size() * 3);
                    qDebug() << texturesArray.size() << normalsArray.size();
                    arraysIsCreated = true;
                }

                for (const QString &line : currentLine.mid(1)) {
                    QStringList temp = line.split("/");
                    int currentVertexPointer = temp.at(0).toInt() - 1;
                    int texutreIndex = temp.at(1).toInt() - 1;
                    int normalIndex = temp.at(2).toInt() - 1;
                    indices.append(currentVertexPointer);
                    QVector2D currnetTexture = textures.at(texutreIndex);
                    QVector3D currentNormal = textures.at(normalIndex);
                    texturesArray[currentVertexPointer * 2 + 0] = currnetTexture.x();
                    texturesArray[currentVertexPointer * 2 + 1] = 1 - currnetTexture.y();
                    normalsArray[currentVertexPointer * 3 + 0] = currentNormal.x();
                    normalsArray[currentVertexPointer * 3 + 1] = currentNormal.y();
                    normalsArray[currentVertexPointer * 3 + 2] = currentNormal.z();
                }
            }
        }
        verticesArray.resize(vertices.size() * 3);
        indicesArray.resize(indices.size());
        int vertexPointer = 0;
        for (const QVector3D &vertex : vertices) {
            verticesArray[vertexPointer++] = vertex.x();
            verticesArray[vertexPointer++] = vertex.y();
            verticesArray[vertexPointer++] = vertex.z();
        }

        for (int i = 0; i < indices.size(); ++i) {
            indicesArray[i] = indices.at(i);
        }
        result = loader->loadDataToVao(verticesArray, texturesArray, indicesArray);
    }
    return result;
}
