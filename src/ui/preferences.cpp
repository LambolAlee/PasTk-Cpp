#include "preferences.h"
#include "ui_preferences.h"

#include "src/settings/config.h"

#include<QMessageBox>


Preferences::Preferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preferences)
{
    ui->setupUi(this);

    for (auto &&language: { "en_US", "zh_CN" }) {
        QLocale locale(language);
        ui->languageCB->addItem(locale.nativeLanguageName(), language);
    }

    int i = 0;
    for (auto &&opt: { "Clear History", "Reserve History" })
        ui->clearHistoryOpt->addItem(opt, i++);

    ui->windowVisibility->addItem("Hide", false);
    ui->windowVisibility->addItem("Show", true);

    Config config;
    // General settings
    for (int i = 0; i < ui->languageCB->count(); ++i) {
        if (ui->languageCB->itemData(i).toString() == config.getLanguage()) {
            ui->languageCB->setCurrentIndex(i);
            break;
        }
    }
    ui->menubarShowOpt->setChecked(config.getMenuBarShow());
    ui->topmostOpt->setChecked(config.getTopmost());
    ui->windowVisibility->setCurrentIndex(config.getWindowVisible());
    ui->clearHistoryOpt->setCurrentIndex(config.getClearAfterNewCopy());

    // Hotkey settings
    ui->copyShortcut->setKeySequence(config.getCopyShortcut());
    ui->runPasteShortcut->setKeySequence(config.getRunPasteShortcut());
    ui->pasteShortcut->setKeySequence(config.getPasteShortcut());
    ui->skipShortcut->setKeySequence(config.getSkipShortcut());

    connectSignalsWithSlots();
}

Preferences::~Preferences()
{
    delete ui;
}

void Preferences::connectSignalsWithSlots()
{
    connect(this, &Preferences::accepted, this, &Preferences::save);
    connect(ui->generalResetBtn, &QPushButton::clicked, this, &Preferences::resetGeneralSettings);
    connect(ui->hotkeyResetBtn, &QPushButton::clicked, this, &Preferences::resetHotkeySettings);
}

void Preferences::save()
{
    Config config;
    // General settings
    config.setLanguage(ui->languageCB->currentData().toString());
    config.setMenuBarShow(ui->menubarShowOpt->isChecked());
    config.setTopmost(ui->topmostOpt->isChecked());
    config.setWindowVisible(ui->windowVisibility->currentData().toBool());
    config.setClearAfterNewCopy((defaults::NewCopyOperation)ui->clearHistoryOpt->currentIndex());

    // Hotkey settings
    config.setCopyShortcut(ui->copyShortcut->keySequence());
    config.setRunPasteShortcut(ui->runPasteShortcut->keySequence());
    config.setPasteShortcut(ui->pasteShortcut->keySequence());
    config.setSkipPasteShortcut(ui->skipShortcut->keySequence());
}

void Preferences::resetGeneralSettings()
{
    if (QMessageBox::question(this, "Reset Confirmation", "Do you want to restore all the general settings?") == QMessageBox::No) return;

    for (int i = 0; i < ui->languageCB->count(); ++i) {
        if (ui->languageCB->itemData(i).toString() == defaults::getQString(defaults::language)) {
            ui->languageCB->setCurrentIndex(i);
            break;
        }
    }
    ui->menubarShowOpt->setChecked(defaults::menuBarShow);
    ui->topmostOpt->setChecked(defaults::topmost);
    ui->windowVisibility->setCurrentIndex(defaults::windowVisibility);
    ui->clearHistoryOpt->setCurrentIndex(defaults::clearAfterNewCopy);
}

void Preferences::resetHotkeySettings()
{
    if (QMessageBox::question(this, "Reset Confirmation", "Do you want to restore all the hotkey settings?") == QMessageBox::No) return;

    ui->copyShortcut->setKeySequence(QKeySequence(defaults::getQString(defaults::copy)));
    ui->runPasteShortcut->setKeySequence(QKeySequence(defaults::getQString(defaults::runPaste)));
    ui->pasteShortcut->setKeySequence(QKeySequence(defaults::getQString(defaults::paste)));
    ui->skipShortcut->setKeySequence(QKeySequence(defaults::getQString(defaults::skip)));
}
