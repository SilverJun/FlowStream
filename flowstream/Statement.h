#ifndef __STATEMENT_H_
#define __STATEMENT_H_

#include "token.h"
#include "SymbolTable.h"

class CStatement				//���๮ �ֻ��� Ŭ����
{
public:
	virtual void Execute(SymbolTable &context);			//���๮ ����.	expression���� Evaluate�� ����.
	static CStatement* Create(tokenItor &itor);			//���๮ ����.	expression���� Parse�� ����.
	virtual ~CStatement();

protected:
	static void Expect(TokenID Expected, const Token &NowToken);			//�������� ������ �����ϱ� ���� �ۼ�.
};

typedef std::shared_ptr<CStatement> StatementPtr;
typedef std::list<StatementPtr> statementList;

#endif
