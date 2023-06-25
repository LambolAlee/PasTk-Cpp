#include "tagsdrawercontent.h"
#include "ui_tagsdrawercontent.h"
#include "src/tag/tagloader.h"


TagsDrawerContent::TagsDrawerContent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TagsDrawerContent)
{
    ui->setupUi(this);

    for (auto [tagName, doc] : TagLoader::instance().tagDoc().asKeyValueRange()) {
        QListWidgetItem *item = new QListWidgetItem(QString("<%1/>").arg(tagName));
        item->setData(Qt::UserRole, doc);
        ui->tagList->addItem(item);
    }

    connect(ui->tagList, &QListWidget::itemClicked, this, &TagsDrawerContent::showDoc);
    connect(ui->tagList, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem *item){ emit tagToBePasted(item->text()); });
}

TagsDrawerContent::~TagsDrawerContent()
{
    delete ui;
}

void TagsDrawerContent::showDoc(QListWidgetItem *item)
{
    ui->helpDoc->setText(item->data(Qt::UserRole).toString());
}
