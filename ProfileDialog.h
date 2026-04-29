#ifndef PROFILEDIALOG_H
#define PROFILEDIALOG_H

#include <QWidget>
#include <QVBoxLayout>
#include "include/player.h"
#include <QDialog>
#include <QTableWidget>

class HistoryDialog : public QDialog 
{
    Q_OBJECT
public:
    HistoryDialog(Player* p, QWidget *parent = nullptr);
};

class ProfileWidget : public QWidget
{
    Q_OBJECT

public:
    ProfileWidget(Player* player, QWidget *parent = nullptr);
    void refresh();

private:
    Player* player;
    QVBoxLayout* statsLayout;
};

#endif
