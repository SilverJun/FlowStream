#include "stdafx.h"

#include "Value.h"
#include "Error.h"

Value operator+(const Value lhs, const Value rhs)
{
	switch (lhs.valueType)
	{
	case ValueType::vInt:
		if (rhs.valueType != vString)
		{
			return (rhs.valueType == vInt) ? Value(vInt, lhs.intValue + rhs.intValue) : Value(vInt, lhs.intValue + rhs.floatValue);
		}
		else
		{
			//throw(Error(std::string("Can`t add int and string ") + *rhs.stringValue));
			return Value(vString, std::string(std::to_string(lhs.intValue) + *rhs.stringValue));
		}
		break;
	case ValueType::vFloat:
		if (rhs.valueType != vString)
		{
			return (rhs.valueType == vFloat) ? Value(vFloat, lhs.floatValue + rhs.floatValue) : Value(vFloat, lhs.floatValue + rhs.intValue);
		}
		else
		{
			//throw(Error(std::string("Can`t add float and string ") + *rhs.stringValue));
			return Value(vString, std::string(std::to_string(lhs.floatValue) + *rhs.stringValue));
		}
		break;
	case ValueType::vString:
		if (rhs.valueType == vString)
		{
			return Value(vString, std::string(*lhs.stringValue + *rhs.stringValue));
		}
		else
		{
			//throw(Error(std::string("Can`t add string and int or float")));
			return (rhs.valueType == vInt) ? Value(vString, *lhs.stringValue + std::to_string(rhs.intValue)) : Value(vString, *lhs.stringValue + std::to_string(rhs.floatValue));
		}
		break;
	default:
		throw(Error(std::string("Invalid ValueType")));
	}
}

Value operator-(const Value lhs, const Value rhs)
{
	switch (lhs.valueType)
	{
	case ValueType::vInt:
		if (rhs.valueType != vString)
		{
			return (rhs.valueType == vInt) ? Value(vInt, lhs.intValue - rhs.intValue) : Value(vInt, lhs.intValue - rhs.floatValue);
		}
		else
		{
			throw(Error(std::string("Can`t minus int and string ") + *rhs.stringValue));
		}
		break;
	case ValueType::vFloat:
		if (rhs.valueType != vString)
		{
			return (rhs.valueType == vFloat) ? Value(vFloat, lhs.floatValue - rhs.floatValue) : Value(vFloat, lhs.floatValue - rhs.intValue);
		}
		else
		{
			throw(Error(std::string("Can`t minus float and string ") + *rhs.stringValue));
		}
		break;
	case ValueType::vString:
		throw(Error(std::string("Can`t minus string") + *lhs.stringValue));
	default:
		throw(Error(std::string("Invalid ValueType")));
	}
}

Value operator*(const Value lhs, const Value rhs)
{
	switch (lhs.valueType)
	{
	case ValueType::vInt:
		if (rhs.valueType != vString)
		{
			return (rhs.valueType == vInt) ? Value(vInt, lhs.intValue * rhs.intValue) : Value(vInt, lhs.intValue * rhs.floatValue);
		}
		else
		{
			throw(Error(std::string("Can`t multi int and string ") + *rhs.stringValue));
		}
		break;
	case ValueType::vFloat:
		if (rhs.valueType != vString)
		{
			return (rhs.valueType == vFloat) ? Value(vFloat, lhs.floatValue * rhs.floatValue) : Value(vFloat, lhs.floatValue * rhs.intValue);
		}
		else
		{
			throw(Error(std::string("Can`t multi float and string ") + *rhs.stringValue));
		}
		break;
	case ValueType::vString:
		throw(Error(std::string("Can`t multi string and int or float")));
		break;
	default:
		throw(Error(std::string("Invalid ValueType")));
	}
}

Value operator/(const Value lhs, const Value rhs)
{
	switch (lhs.valueType)
	{
	case ValueType::vInt:
		if (rhs.valueType != vString)
		{
			return (rhs.valueType == vInt) ? Value(vInt, lhs.intValue / rhs.intValue) : Value(vInt, lhs.intValue / rhs.floatValue);
		}
		else
		{
			throw(Error(std::string("Can`t divide int and string ") + *rhs.stringValue));
		}
		break;
	case ValueType::vFloat:
		if (rhs.valueType != vString)
		{
			return (rhs.valueType == vFloat) ? Value(vFloat, lhs.floatValue / rhs.floatValue) : Value(vFloat, lhs.floatValue / rhs.intValue);
		}
		else
		{
			throw(Error(std::string("Can`t divide float and string ") + *rhs.stringValue));
		}
		break;
	case ValueType::vString:
		throw(Error(std::string("Can`t divide string and int or float")));
		break;
	default:
		throw(Error(std::string("Invalid ValueType")));
	}
}

Value operator%(const Value lhs, const Value rhs)
{
	switch (lhs.valueType)
	{
	case ValueType::vInt:
		if (rhs.valueType != vString)
		{
			if (rhs.valueType == vFloat)
			{
				//throw(Error(std::string("Can`t mod int and float")));
				return Value(vInt, std::fmodf(lhs.intValue , rhs.floatValue));
			}
			else
			{
				return Value(vInt, lhs.intValue % rhs.intValue);
			}
		}
		else
		{
			throw(Error(std::string("Can`t mod int and string ") + *rhs.stringValue));
		}
		break;
	case ValueType::vFloat:
		//throw(Error(std::string("Can`t mod float")));
		if (rhs.valueType != vString)
		{
			return (rhs.valueType == vInt) ? Value(vInt, std::fmodf(lhs.floatValue, rhs.intValue)) : Value(vInt, std::fmodf(lhs.floatValue, rhs.floatValue));
		}
		else
		{
			throw(Error(std::string("Can`t mod float and string ") + *rhs.stringValue));
		}
		break;
	case ValueType::vString:
		throw(Error(std::string("Can`t mod string")));
		break;
	default:
		throw(Error(std::string("Invalid ValueType")));
	}
}


Value operator<(const Value lhs, const Value rhs)
{
	switch (lhs.valueType)
	{
	case ValueType::vInt:
		switch (rhs.valueType)
		{
		case ValueType::vInt:
			return Value(vInt, lhs.intValue < rhs.intValue);
		case ValueType::vFloat:
			return Value(vInt, lhs.intValue < rhs.floatValue);
		case ValueType::vString:
			throw(Error(std::string("Can`t Compare int and string")));
		}
		break;
	case ValueType::vFloat:
		switch (rhs.valueType)
		{
		case ValueType::vInt:
			return Value(vInt, lhs.floatValue < rhs.intValue);
		case ValueType::vFloat:
			return Value(vInt, lhs.floatValue < rhs.floatValue);
		case ValueType::vString:
			throw(Error(std::string("Can`t Compare int and string")));
		}
		break;
	case ValueType::vString:
		switch (rhs.valueType)
		{
		case ValueType::vInt:
			throw(Error(std::string("Can`t Compare string and int")));
		case ValueType::vFloat:
			throw(Error(std::string("Can`t Compare string and float")));
		case ValueType::vString:
			return Value(vInt, *lhs.stringValue < *rhs.stringValue);
		}
		break;
	default:
		throw(Error(std::string("Invalid ValueType")));
		break;
	}
}

Value operator>(const Value lhs, const Value rhs)
{
	switch (lhs.valueType)
	{
	case ValueType::vInt:
		switch (rhs.valueType)
		{
		case ValueType::vInt:
			return Value(vInt, lhs.intValue > rhs.intValue);
		case ValueType::vFloat:
			return Value(vInt, lhs.intValue > rhs.floatValue);
		case ValueType::vString:
			throw(Error(std::string("Can`t Compare int and string")));
		}
		break;
	case ValueType::vFloat:
		switch (rhs.valueType)
		{
		case ValueType::vInt:
			return Value(vInt, lhs.floatValue > rhs.intValue);
		case ValueType::vFloat:
			return Value(vInt, lhs.floatValue > rhs.floatValue);
		case ValueType::vString:
			throw(Error(std::string("Can`t Compare int and string")));
		}
		break;
	case ValueType::vString:
		switch (rhs.valueType)
		{
		case ValueType::vInt:
			throw(Error(std::string("Can`t Compare string and int")));
		case ValueType::vFloat:
			throw(Error(std::string("Can`t Compare string and float")));
		case ValueType::vString:
			return Value(vInt, *lhs.stringValue > *rhs.stringValue);
		}
		break;
	default:
		throw(Error(std::string("Invalid ValueType")));
		break;
	}
}

Value operator<=(const Value lhs, const Value rhs)
{
	switch (lhs.valueType)
	{
	case ValueType::vInt:
		switch (rhs.valueType)
		{
		case ValueType::vInt:
			return Value(vInt, lhs.intValue <= rhs.intValue);
		case ValueType::vFloat:
			return Value(vInt, lhs.intValue <= rhs.floatValue);
		case ValueType::vString:
			throw(Error(std::string("Can`t Compare int and string")));
		}
		break;
	case ValueType::vFloat:
		switch (rhs.valueType)
		{
		case ValueType::vInt:
			return Value(vInt, lhs.floatValue <= rhs.intValue);
		case ValueType::vFloat:
			return Value(vInt, lhs.floatValue <= rhs.floatValue);
		case ValueType::vString:
			throw(Error(std::string("Can`t Compare int and string")));
		}
		break;
	case ValueType::vString:
		switch (rhs.valueType)
		{
		case ValueType::vInt:
			throw(Error(std::string("Can`t Compare string and int")));
		case ValueType::vFloat:
			throw(Error(std::string("Can`t Compare string and float")));
		case ValueType::vString:
			return Value(vInt, *lhs.stringValue <= *rhs.stringValue);
		}
		break;
	default:
		throw(Error(std::string("Invalid ValueType")));
		break;
	}
}

Value operator>=(const Value lhs, const Value rhs)
{
	switch (lhs.valueType)
	{
	case ValueType::vInt:
		switch (rhs.valueType)
		{
		case ValueType::vInt:
			return Value(vInt, lhs.intValue >= rhs.intValue);
		case ValueType::vFloat:
			return Value(vInt, lhs.intValue >= rhs.floatValue);
		case ValueType::vString:
			throw(Error(std::string("Can`t Compare int and string")));
		}
		break;
	case ValueType::vFloat:
		switch (rhs.valueType)
		{
		case ValueType::vInt:
			return Value(vInt, lhs.floatValue >= rhs.intValue);
		case ValueType::vFloat:
			return Value(vInt, lhs.floatValue >= rhs.floatValue);
		case ValueType::vString:
			throw(Error(std::string("Can`t Compare int and string")));
		}
		break;
	case ValueType::vString:
		switch (rhs.valueType)
		{
		case ValueType::vInt:
			throw(Error(std::string("Can`t Compare string and int")));
		case ValueType::vFloat:
			throw(Error(std::string("Can`t Compare string and float")));
		case ValueType::vString:
			return Value(vInt, *lhs.stringValue >= *rhs.stringValue);
		}
		break;
	default:
		throw(Error(std::string("Invalid ValueType")));
		break;
	}
}

Value operator!=(const Value lhs, const Value rhs)
{
	switch (lhs.valueType)
	{
	case ValueType::vInt:
		switch (rhs.valueType)
		{
		case ValueType::vInt:
			return Value(vInt, lhs.intValue != rhs.intValue);
		case ValueType::vFloat:
			return Value(vInt, lhs.intValue != rhs.floatValue);
		case ValueType::vString:
			throw(Error(std::string("Can`t Compare int and string")));
		}
		break;
	case ValueType::vFloat:
		switch (rhs.valueType)
		{
		case ValueType::vInt:
			return Value(vInt, lhs.floatValue != rhs.intValue);
		case ValueType::vFloat:
			return Value(vInt, lhs.floatValue != rhs.floatValue);
		case ValueType::vString:
			throw(Error(std::string("Can`t Compare int and string")));
		}
		break;
	case ValueType::vString:
		switch (rhs.valueType)
		{
		case ValueType::vInt:
			throw(Error(std::string("Can`t Compare string and int")));
		case ValueType::vFloat:
			throw(Error(std::string("Can`t Compare string and float")));
		case ValueType::vString:
			return Value(vInt, *lhs.stringValue != *rhs.stringValue);
		}
		break;
	default:
		throw(Error(std::string("Invalid ValueType")));
		break;
	}
}

Value operator==(const Value lhs, const Value rhs)
{
	switch (lhs.valueType)
	{
	case ValueType::vInt:
		switch (rhs.valueType)
		{
		case ValueType::vInt:
			return Value(vInt, lhs.intValue == rhs.intValue);
		case ValueType::vFloat:
			return Value(vInt, lhs.intValue == rhs.floatValue);
		case ValueType::vString:
			throw(Error(std::string("Can`t Compare int and string")));
		}
		break;
	case ValueType::vFloat:
		switch (rhs.valueType)
		{
		case ValueType::vInt:
			return Value(vInt, lhs.floatValue == rhs.intValue);
		case ValueType::vFloat:
			return Value(vInt, lhs.floatValue == rhs.floatValue);
		case ValueType::vString:
			throw(Error(std::string("Can`t Compare int and string")));
		}
		break;
	case ValueType::vString:
		switch (rhs.valueType)
		{
		case ValueType::vInt:
			throw(Error(std::string("Can`t Compare string and int")));
		case ValueType::vFloat:
			throw(Error(std::string("Can`t Compare string and float")));
		case ValueType::vString:
			return Value(vInt, *lhs.stringValue == *rhs.stringValue);
		}
		break;
	default:
		throw(Error(std::string("Invalid ValueType")));
		break;
	}
}


Value operator&(const Value lhs, const Value rhs)
{
	switch (lhs.valueType)
	{
	case ValueType::vInt:
		if (rhs.valueType != vString)
		{
			if (rhs.valueType == vFloat)
			{
				throw(Error(std::string("Can`t bitand int and float")));
			}
			else
			{
				return Value(vInt, lhs.intValue & rhs.intValue);
			}
		}
		else
		{
			throw(Error(std::string("Can`t bitand int and string ") + *rhs.stringValue));
		}
		break;
	case ValueType::vFloat:
		throw(Error(std::string("Can`t bitand float")));
		break;
	case ValueType::vString:
		throw(Error(std::string("Can`t bitand string")));
		break;
	default:
		throw(Error(std::string("Invalid ValueType")));
	}
}

Value operator|(const Value lhs, const Value rhs)
{
	switch (lhs.valueType)
	{
	case ValueType::vInt:
		if (rhs.valueType != vString)
		{
			if (rhs.valueType == vFloat)
			{
				throw(Error(std::string("Can`t bitor int and float")));
			}
			else
			{
				return Value(vInt, lhs.intValue | rhs.intValue);
			}
		}
		else
		{
			throw(Error(std::string("Can`t bitor int and string ") + *rhs.stringValue));
		}
		break;
	case ValueType::vFloat:
		throw(Error(std::string("Can`t bitor float")));
		break;
	case ValueType::vString:
		throw(Error(std::string("Can`t bitor string")));
		break;
	default:
		throw(Error(std::string("Invalid ValueType")));
	}
}


Value operator&&(const Value lhs, const Value rhs)
{
	switch (lhs.valueType)
	{
	case ValueType::vInt:
		switch (rhs.valueType)
		{
		case ValueType::vInt:
			return Value(vInt, lhs.intValue && rhs.intValue);
		case ValueType::vFloat:
			return Value(vInt, lhs.intValue && rhs.floatValue);
		case ValueType::vString:
			throw(Error(std::string("Can`t and int and string")));
		}
		break;
	case ValueType::vFloat:
		switch (rhs.valueType)
		{
		case ValueType::vInt:
			return Value(vInt, lhs.floatValue && rhs.intValue);
		case ValueType::vFloat:
			return Value(vInt, lhs.floatValue && rhs.floatValue);
		case ValueType::vString:
			throw(Error(std::string("Can`t and int and string")));
		}
		break;
	case ValueType::vString:
		throw(Error(std::string("Can`t and string")));
		break;
	default:
		throw(Error(std::string("Invalid ValueType")));
		break;
	}
}

Value operator||(const Value lhs, const Value rhs)
{
	switch (lhs.valueType)
	{
	case ValueType::vInt:
		switch (rhs.valueType)
		{
		case ValueType::vInt:
			return Value(vInt, lhs.intValue || rhs.intValue);
		case ValueType::vFloat:
			return Value(vInt, lhs.intValue || rhs.floatValue);
		case ValueType::vString:
			throw(Error(std::string("Can`t or int and string")));
		}
		break;
	case ValueType::vFloat:
		switch (rhs.valueType)
		{
		case ValueType::vInt:
			return Value(vInt, lhs.floatValue || rhs.intValue);
		case ValueType::vFloat:
			return Value(vInt, lhs.floatValue || rhs.floatValue);
		case ValueType::vString:
			throw(Error(std::string("Can`t or int and string")));
		}
		break;
	case ValueType::vString:
		throw(Error(std::string("Can`t or string")));
		break;
	default:
		throw(Error(std::string("Invalid ValueType")));
		break;
	}
}


Value Value::operator!()
{
	switch (this->valueType)
	{
	case ValueType::vInt:
		return Value(vInt, !(this->intValue));
	case ValueType::vFloat:
		return Value(vFloat, !(this->floatValue));
	case ValueType::vString:
		return Value(vString, !(this->stringValue));
	default:
		throw(Error(std::string("Invalid ValueType")));
		break;
	}
}


Value Value::operator++(int back)
{
	switch (this->valueType)
	{
	case ValueType::vInt:
		this->intValue++;
		return *this;
	case ValueType::vFloat:
		this->floatValue++;
		return *this;
	case ValueType::vString:
		throw(Error(std::string("Can`t increment string")));
		break;
	default:
		throw(Error(std::string("Invalid ValueType")));
		break;
	}
}

Value Value::operator--(int back)
{
	switch (this->valueType)
	{
	case ValueType::vInt:
		this->intValue--;
		return *this;
	case ValueType::vFloat:
		this->floatValue--;
		return *this;
	case ValueType::vString:
		throw(Error(std::string("Can`t increment string")));
		break;
	default:
		throw(Error(std::string("Invalid ValueType")));
		break;
	}
}

Value Value::operator=(const Value rhs)
{
	switch (this->valueType)
	{
	case ValueType::vInt:
		switch (rhs.valueType)
		{
		case ValueType::vInt:
			this->intValue = rhs.intValue;
			return *this;
		case ValueType::vFloat:
			this->intValue = rhs.floatValue;
			return *this;
		case ValueType::vString:
			throw(Error(std::string("Can`t store int variable in string") + *rhs.stringValue));
			break;
		default:
			throw(Error(std::string("Invalid ValueType")));
			break;
		}
		return *this;
	case ValueType::vFloat:
		switch (rhs.valueType)
		{
		case ValueType::vInt:
			this->floatValue = rhs.intValue;
			return *this;
		case ValueType::vFloat:
			this->floatValue = rhs.floatValue;
			return *this;
		case ValueType::vString:
			throw(Error(std::string("Can`t store float variable in string") + *rhs.stringValue));
			break;
		default:
			throw(Error(std::string("Invalid ValueType")));
			break;
		}
		return *this;
	case ValueType::vString:
		switch (rhs.valueType)
		{
		case ValueType::vInt:
			throw(Error(std::string("Can`t store string variable in int")));
			return *this;
		case ValueType::vFloat:
			throw(Error(std::string("Can`t store string variable in float")));
			return *this;
		case ValueType::vString:
			delete this->stringValue;
			this->stringValue = rhs.stringValue;
			return *this;
			break;
		default:
			throw(Error(std::string("Invalid ValueType")));
			break;
		}
		break;
	case vNull:
		this->valueType = rhs.valueType;
		this->operator=(rhs);
		return *this;
		break;
	default:
		throw(Error(std::string("Invalid ValueType")));
		break;
	}
}