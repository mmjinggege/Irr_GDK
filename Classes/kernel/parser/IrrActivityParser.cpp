#include "IrrActivityParser.h"
#include "IrrMarcos.h"
#include "IrrStringUtils.h"
#include "IrrMemoCacheManager.h"
#include "IrrPattern.h"

using namespace irr_manager;

namespace irr_core
{

	IrrActivityParser::IrrActivityParser( void )
	{
	}

	IrrActivityParser::~IrrActivityParser( void )
	{
	}

	void IrrActivityParser::parserActivityConfigure( const char* cfgXml )
	{
		if(cfgXml == NULL) return;
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(cfgXml);
		if(result)
		{
			pugi::xml_node root = doc.child("IrrManifest").first_child();
			pugi::xml_node activieChild = root.child("Activitys").first_child();
			while(!activieChild.empty())
			{
				__parserActivity__(activieChild);
				activieChild = activieChild.next_sibling();
			}

			pugi::xml_node observerChild = root.child("NetObservers").first_child();
			while(!observerChild.empty())
			{
				__parserNetObserver__(observerChild);
				observerChild = observerChild.next_sibling();
			}
		}
	}


	void IrrActivityParser::__parserActivity__(pugi::xml_node node)
	{
		IrrActivity* acvitiy = new IrrActivity();
		int id = irr_utils::IrrStringUtils::StringToInt(node.attribute("id").value());
		int netObserverID = irr_utils::IrrStringUtils::StringToInt(node.attribute("NetObserverID").value());
		acvitiy->setObjectID(id);
		acvitiy->setNetObserverID(netObserverID);
		IrrMemoCacheMgr->pushMemoCache(IRR_ACTIVITY,acvitiy);
	}


	void IrrActivityParser::__parserNetObserver__( pugi::xml_node node )
	{
		IrrNetObserver* observe = new IrrNetObserver();
		int id = irr_utils::IrrStringUtils::StringToInt(node.attribute("id").value());
		pugi::xml_node commandChild = node.child("Commanders").first_child();
		while(!commandChild.empty())
		{
			int commandID = irr_utils::IrrStringUtils::StringToInt(commandChild.attribute("id").value());
			//IrrCommand* pCommander = new IrrCommand();
			commandChild = commandChild.next_sibling();
		}
		observe->setObjectID(id);
		IrrMemoCacheMgr->pushMemoCache(IRR_NET_OBSERVER,observe);
	}
}