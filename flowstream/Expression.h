#ifndef __EXPRESSION_H_
#define __EXPRESSION_H_

#include "Token.h"
#include "Value.h"
#include "SymbolTable.h"

class CExpression		//ǥ������ ���� �⺻�� �Ǵ� �ֻ��� �θ� Ŭ����
{
public:
	typedef std::shared_ptr<CExpression> ExprPtr;		//shared_ptr�� �ѹ� �������ش�.
	typedef std::list<ExprPtr> Exprs;			//����Ʈ�� ����
	typedef std::shared_ptr<Exprs> ExprsPtr;		//����Ʈ�� shared_ptr�� �ѹ� �������ش�.
	static ExprPtr Parse(tokenItor &it);			//ǥ������ �м��ϰ� �Ľ�Ʈ���� �����.
	virtual Value Evaluate(SymbolTable &context) = 0;		//�м��� �Ľ�Ʈ���� �������� ���� ����ذ���.
	virtual ~CExpression() {};
protected:
	static void Expect(TokenID Expected, const Token &NowToken);		//������ �´��� Ȯ���Ѵ�.
};

#endif
