
#include "TableViewController.h"


//
// DataSource
//
TableViewController::TableViewController( CCSize size ) 
	: _bar(0)
{
	_dmgr = DataManager::Self();
	
	SetCellSize( size );
}

TableViewController::~TableViewController() 
{

}

unsigned int TableViewController::numberOfCellsInTableView(CCTableView *table) {
	return _dmgr->GetData().size();
}

CCSize TableViewController::cellSizeForTable(CCTableView *table) {
	return _cellSize;
}

CCTableViewCell* TableViewController::tableCellAtIndex(CCTableView *table, unsigned int idx) {

	TableViewCell *cell = (TableViewCell*)table->dequeueCell();

	if (cell == NULL) {
		cell = new TableViewCell;
		cell->setContentSize( _cellSize );
	}

	CCString *str = CCString::createWithFormat( "C%d", _dmgr->GetData()[idx] );
	cell->GetLabel()->setString( str->getCString() );

	return cell;
}


//
// Delegate
//
void TableViewController::scrollViewDidScroll(CCScrollView* view) 
{
	if(_bar != NULL) 
	{
		_bar->Refresh();
	}
}

void TableViewController::scrollViewDidZoom(CCScrollView* view)
{

}

void TableViewController::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	int p = cell->getIdx();

	CCPoint offset = table->getContentOffset();

	table->removeCellAtIndex(p);
	table->reloadData();
	
	//������� �ϸ� �� ���������� ���ڽ��� ������ �� ���� ��������. �׷��ٰ� ���ϴ� �ε��� ��ġ�� �̵��ϴ� �޼ҵ�� ����. ���̺�並 Ȯ���� ���� �ְ�����, �ϴ� �����Ǵ� ��ɸ����� ���ϴ� ���۸ս��� ����� ���ڴ�.
	if(p > 4) 
		table->setContentOffset(offset); //������ ����� ��� ��ũ�� ���� �������� ����ߴٰ� �ٽ÷ε� �� �������ش�. ���� 4 (ȭ�鿡 �������� �� ����)�� ������ 4���� �������� ��.. �������� �ٽ� �����Ǹ� �̻��ϰ� �۵��ϱ� �����̴�. �׸��� ���ε��ϸ� �� ���� ���µ� ���� ������ �ʿ䰡 ��� �̱⵵ �ϴ�.
}

void TableViewController::tableCellHighlight(CCTableView* table, CCTableViewCell* cell)
{
	CCLayerColor* mask;
	mask = CCLayerColor::create( ccc4(200, 0, 0, 100), _cellSize.width, _cellSize.height );
	cell->addChild( mask, 100, COLOR_LAYER_TAG );
}

void TableViewController::tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell)
{
	cell->removeChildByTag( COLOR_LAYER_TAG, true );
}