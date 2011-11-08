/***************************************************************************
 *   Copyright (C) 2011 by Kristian Karl kristian.hermann.karl@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/

// Here we avoid loading the header multiple times
#ifndef MYPLASMOID_HEADER
#define MYPLASMOID_HEADER

#include <Plasma/Applet>
#include <QNetworkAccessManager>
#include <QXmlStreamReader>

class QSizeF;

// Define our plasma Applet
class narGarTagetHemPlasmoid : public Plasma::Applet {
    Q_OBJECT
  public:
    // Basic Create/Destroy
    narGarTagetHemPlasmoid ( QObject *parent, const QVariantList &args );
    ~narGarTagetHemPlasmoid();

    // The paintInterface procedure paints the applet to the desktop
    void paintInterface ( QPainter *painter,
                          const QStyleOptionGraphicsItem *option,
                          const QRect& contentsRect );
    void init();

  public slots:
    void updateDeparture();
    void replyFinished ( QNetworkReply* );

  private:
    int getData ( QTextStream*, const QString& siteId, const QString& journeyDirection );
    void processResult ( QIODevice* );
    QMap<QString, QString>  readTrain ( QXmlStreamReader& );
    void addElementDataToMap ( QXmlStreamReader& xml, QMap<QString, QString>& map ) const;

  private:
    QNetworkAccessManager* manager;
    QList< QMap<QString,QString> > trains;
    QString stockholmsCentral;
    QString ronningeStation;
};

// This is the command that links your applet to the .desktop file
K_EXPORT_PLASMA_APPLET ( narGarTagetHemPlasmoid, narGarTagetHemPlasmoid )
#endif
