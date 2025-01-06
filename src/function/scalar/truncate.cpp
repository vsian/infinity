module;

#include <cmath>

module truncate;

import stl;
import catalog;
import logical_type;
import infinity_exception;
import scalar_function;
import scalar_function_set;

import third_party;
import internal_types;
import data_type;

namespace infinity {

struct TruncateFunction {
    template <typename FirstSourceType, typename SecondSourceType, typename TargetType>
    static inline bool Run(FirstSourceType base,  SecondSourceType exp, TargetType &result) {
        
        if (std::isnan(base) || std::isinf(base) || std::isnan(exp) || std::isinf(exp)) {
            return false;
        }
        if (exp < static_cast<SecondSourceType>(0)) {
            return false;
        }
        if (exp == 0) {
            result = base;
        } else {
            double mask = std::pow(10.0, exp);
            result = round(static_cast<double>(base * mask)) / mask;
        }
        
        return true;
    }
};

void RegisterSqrtFunction(const UniquePtr<Catalog> &catalog_ptr) {
    String func_name = "truncate";

    SharedPtr<ScalarFunctionSet> function_set_ptr = MakeShared<ScalarFunctionSet>(func_name);

    ScalarFunction truncate_float_int8(func_name,
                              {DataType(LogicalType::kFloat), DataType(LogicalType::kTinyInt)},
                              DataType(LogicalType::kDouble),
                              &ScalarFunction::BinaryFunction<float, TinyIntT, double, TruncateFunction>);
    function_set_ptr->AddFunction(truncate_float_int8);

    ScalarFunction truncate_float_int16(func_name,
                              {DataType(LogicalType::kFloat), DataType(LogicalType::kSmallInt)},
                              DataType(LogicalType::kDouble),
                              &ScalarFunction::BinaryFunction<float, SmallIntT, double, TruncateFunction>);
    function_set_ptr->AddFunction(truncate_float_int16);

    ScalarFunction truncate_float_int32(func_name,
                              {DataType(LogicalType::kFloat), DataType(LogicalType::kInteger)},
                              DataType(LogicalType::kDouble),
                              &ScalarFunction::BinaryFunction<float, IntegerT, double, TruncateFunction>);
    function_set_ptr->AddFunction(truncate_float_int32);

    ScalarFunction truncate_float_int64(func_name,
                              {DataType(LogicalType::kFloat), DataType(LogicalType::kBigInt)},
                              DataType(LogicalType::kDouble),
                              &ScalarFunction::BinaryFunction<float, BigIntT, double, TruncateFunction>);
    function_set_ptr->AddFunction(truncate_float_int64);

    ScalarFunction truncate_double_int8(func_name,
                              {DataType(LogicalType::kDouble), DataType(LogicalType::kTinyInt)},
                              DataType(LogicalType::kDouble),
                              &ScalarFunction::BinaryFunction<double,  TinyIntT, double, TruncateFunction>);
    function_set_ptr->AddFunction(truncate_double_int8);

    ScalarFunction truncate_double_int16(func_name,
                              {DataType(LogicalType::kDouble), DataType(LogicalType::kSmallInt)},
                              DataType(LogicalType::kDouble),
                              &ScalarFunction::BinaryFunction<double,  SmallIntT, double, TruncateFunction>);
    function_set_ptr->AddFunction(truncate_double_int16);

    ScalarFunction truncate_double_int32(func_name,
                              {DataType(LogicalType::kDouble), DataType(LogicalType::kInteger)},
                              DataType(LogicalType::kDouble),
                              &ScalarFunction::BinaryFunction<double, IntegerT, double, TruncateFunction>);
    function_set_ptr->AddFunction(truncate_double_int32);

    ScalarFunction truncate_double_int64(func_name,
                              {DataType(LogicalType::kDouble), DataType(LogicalType::kBigInt)},
                              DataType(LogicalType::kDouble),
                              &ScalarFunction::BinaryFunction<double, BigIntT, double, TruncateFunction>);
    function_set_ptr->AddFunction(truncate_double_int64);


    Catalog::AddFunctionSet(catalog_ptr.get(), function_set_ptr);
}

} // namespace infinity