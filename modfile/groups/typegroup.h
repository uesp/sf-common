#ifndef __SFWIKI_TYPEGROUP_H
#define __SFWIKI_TYPEGROUP_H


#include "group.h"


namespace sfwiki {

	class CTypeGroup : public CGroup {

		/*---------- Begin Private Class Members ----------------------*/
	private:


		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CTypeGroup() : CGroup() { }
		//virtual ~CTypeGroup() { Destroy(); }
		//virtual void Destroy (void);

		  /* Attempt to add a child record */
		bool AddChildRecord(CBaseRecord* pNewRecord);
		//bool IsValidChild   (CSrBaseRecord* pNewRecord);

		  /* Delete a child record */
		bool DeleteChildRecord(CBaseRecord* pRecord);

		/* Return a new class instance */
		static CGroup* Create(void) { return (new CTypeGroup); }

		/* Get class members */
		const rectype_t GetContainsType(void) const { return (m_Header.Data.ContainsType); }

		/* Get class members */
		void SetContainsType(const rectype_t Type) { memcpy(m_Header.Data.ContainsType, Type.Name, RECTYPE_SIZE); }

	};

	
}
#endif
