// Copyright (c) 2011 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>
#include "ui_viewer.h"

namespace WebVfx
{
    class Image;
    class WebPage;
}

class QLabel;
class QWebView;

class Viewer : public QMainWindow, private Ui::Viewer
{
    Q_OBJECT

public:
    Viewer(QWidget *parent = 0);

private slots:
    void on_actionOpen_triggered(bool);
    void on_resizeButton_clicked();
    void on_timeSlider_valueChanged(int);
    void on_addParameterButton_clicked();
    void on_deleteParameterButton_clicked();
    void onImageChanged(const QString& name, const WebVfx::Image& image);

private:
    bool loadPage(const QUrl& url);
    void setupImages(const QSize& size);
    double sliderTimeValue(int value);
    QLabel* sizeLabel;
    QLabel* timeLabel;
    QWebView* webView;
    WebVfx::WebPage* webPage;
};

#endif

