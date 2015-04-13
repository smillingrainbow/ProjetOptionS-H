/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "geometryengine.h"
#include "infoview.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QString>

class GeometryEngine;

class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    /**
     * @brief MainWidget constructeur du MainWidget
     * @param parent
     */
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

protected:
    //override des Event du OpenGL
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *e) Q_DECL_OVERRIDE;

    /**
      *@brief keyPressEvent ajouter des manipulations du OpenGL par clavier
      */
    void keyPressEvent(QKeyEvent *e) Q_DECL_OVERRIDE;

    /**
      *@brief initializeGL init des composants de la fenêtre du OpenGL
      */
    void initializeGL() Q_DECL_OVERRIDE;

    /**
      *@brief resizeGL init le point de vue des Scènes Scenes perspective composant:
      * resize la taille de la fenêtre du OpenGL et initi des chiffres de la sènce de projection
      *@param w width/largeur
      *@param h height/longeur
      */
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;

    /**
      *@brief paintGL dessiner la fenêtre du OpenGL
      * chaque fois il y a des events de mis à jour, cette fonction est appelée
      */
    void paintGL() Q_DECL_OVERRIDE;

    /**
     * @brief initShaders
     */
    void initShaders();

    /**
     * @brief initTextures init du textures
     */
    void initTextures();

    /**
     * @brief initPositions init des coordonnées de la position du cube
     */
    void initPositions();

    /**
     * @brief initInfoView init des fenêtres du InfoView
     */
    void initInfoView();

    /**
     * @brief callCubeBelow appel la fenêtre d'information du cube en base
     * et sorti le cube dans 3D
     */
    void callCubeBelow();

    /**
     * @brief callCubeLeft appel la fenêtre d'information du cube à gauche
     * et sorti le cube dans 3D
     */
    void callCubeLeft();

    /**
     * @brief callCubeRight appel la fenêtre d'information du cube à droit
     * et sorti le cube dans 3D
     */
    void callCubeRight();

    /**
     * @brief showInfo affichage des info du cube
     * @param cube le nom du cube:"below","left" "right"
     */
    void showInfo(QString cube);

private:
    QBasicTimer timer;
    QOpenGLShaderProgram program;
    GeometryEngine *geometries;

    QOpenGLTexture *texture;

    QMatrix4x4 projection;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed;
    QQuaternion rotation;

    /**
     * @brief bool is the info window of cerveau is once opened
     * IsCalledL(left),IsCalledR(right),IsCalledB(base)
     */
    bool IsCalledL,IsCalledR,IsCalledB;
    /**
     * @brief pxL,pyL,pzL des coordonnées de la position du cerveau à gauche
     */
    int pxL,pyL,pzL;
    /**
     * @brief pxR,pyR,pzR des coordonnées de la position du cerveau à droite
     */
    int pxR,pyR,pzR;
    /**
     * @brief pxB,pyB,pzB des coordonnées de la position du cerveau en base
     */
    int pxB,pyB,pzB;


    //The 3 InfoView window
    InfoView *infoViewL,*infoViewR,*infoViewB;

};

#endif // MAINWIDGET_H
