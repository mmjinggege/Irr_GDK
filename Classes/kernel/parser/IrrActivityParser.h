#ifndef _IRRACTIVITYPARSER_H_
#define _IRRACTIVITYPARSER_H_

#include "IrrSingleton.h"
#include "pugixml/pugixml.hpp"
#include "pugixml/pugiconfig.hpp"

namespace irr_core
{
	//////////////////////////////////////////////////////////////////////////
	class IrrActivityParser : public irr_base::IrrSingleton<IrrActivityParser>
	{
	public:
		void parserActivityConfigure(const char* cfgXml);
	protected:
		void __parserActivity__(pugi::xml_node node);
		void __parserNetObserver__(pugi::xml_node node);
	private:
		friend class irr_base::IrrSingleton<IrrActivityParser>;
		IrrActivityParser(void);
		~IrrActivityParser(void);
	};
}

#endif	//_IRRACTIVITYPARSER_H_