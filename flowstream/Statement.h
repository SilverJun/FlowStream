#ifndef __STATEMENT_H_
#define __STATEMENT_H_

#include "token.h"
#include "SymbolTable.h"

class CStatement				//실행문 최상위 클래스
{
public:
	virtual void Execute(SymbolTable &context);			//실행문 실행.	expression에서 Evaluate와 유사.
	static CStatement* Create(tokenItor &itor);			//실행문 생성.	expression에서 Parse와 유사.
	virtual ~CStatement();

protected:
	static void Expect(TokenID Expected, const Token &NowToken);			//문법적인 오류를 검출하기 위해 작성.
};

typedef std::shared_ptr<CStatement> StatementPtr;
typedef std::list<StatementPtr> statementList;

#endif
