//  This file is part of Qt Bitcoin Trader
//      https://github.com/JulyIGHOR/QtBitcoinTrader
//  Copyright (C) 2013-2022 July Ighor <julyighor@gmail.com>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  In addition, as a special exception, the copyright holders give
//  permission to link the code of portions of this program with the
//  OpenSSL library under certain conditions as described in each
//  individual source file, and distribute linked combinations including
//  the two.
//
//  You must obey the GNU General Public License in all respects for all
//  of the code used other than OpenSSL. If you modify file(s) with this
//  exception, you may extend this exception to your version of the
//  file(s), but you are not obligated to do so. If you do not wish to do
//  so, delete this exception statement from your version. If you delete
//  this exception statement from all source files in the program, then
//  also delete it here.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef ORDERSMODEL_H
#define ORDERSMODEL_H

#include "orderitem.h"
#include <QAbstractItemModel>
#include <QStringList>

class OrdersModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    int getAsksCount() const;
    int getRowNum(int row);
    QByteArray getRowOid(int row);
    quint32 getRowDate(int row);
    int getRowType(int row);
    int getRowStatus(int row);
    double getRowPrice(int row);
    double getRowVolume(int row);
    double getRowTotal(int row);

    QMap<double, bool> currentAsksPrices;
    QMap<double, bool> currentBidsPrices;

    bool checkDuplicatedOID;
    void ordersCancelAll(const QString& pair = 0);
    void ordersCancelBids(const QString& pair = 0);
    void ordersCancelAsks(const QString& pair = 0);
    void setOrderCanceled(QByteArray);

    void filterSymbolChanged(const QString& filterSymbol = "");

    void clear();

    OrdersModel();
    ~OrdersModel();

    void orderBookChanged(QList<OrderItem>* ordersRcv);

    void setHorizontalHeaderLabels(QStringList list);

    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex& index) const;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex& index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;

    QList<OrderItem> orders;

signals:
    void cancelOrder(const QString&, const QByteArray&);
    void ordersIsAvailable();
    void volumeAmountChanged(double, double);

private:
    void ordersCountChanged();
    void ordersAsksCountChanged();
    void ordersBidsCountChanged();

    int lastOrdersCount;
    int lastAsksCount;
    int lastBidsCount;

    int asksCount;

    QHash<QByteArray, quint32> oidMapForCheckingDuplicates;
    QStringList textStatusList;
    QString textAsk;
    QString textBid;

    bool haveOrders;

    int countWidth;
    int columnsCount;
    int dateWidth;
    int typeWidth;
    int statusWidth;

    QStringList headerLabels;

    QList<QByteArray> oidList;

    QList<quint32> dateList;
    QStringList dateStrList;

    QList<bool> typesList;

    QList<int> statusList;

    QList<double> amountList;
    QStringList amountStrList;

    QList<double> priceList;
    QStringList priceStrList;

    QList<double> totalList;
    QStringList totalStrList;

    QStringList symbolList;
};

#endif // ORDERSMODEL_H
