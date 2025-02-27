#include "jit.test.h"

template<typename T>
T add(T a, T b)
{
    return a + b;
}

template<typename T>
T sub(T a, T b)
{
    return a - b;
}

template<typename T>
T mul(T a, T b)
{
    return a * b;
}

template<typename T>
T div(T a, T b)
{
    return a / b;
}

TEST_F(JITTestRunner, Int16Addition)
{
    this->TestBinOp<std::int16_t>("add_int16", &city::IRBuilder::InsertAddInst, add<std::int16_t>);
}

TEST_F(JITTestRunner, UInt16Addition)
{
    this->TestBinOp<std::uint16_t>("add_uint16", &city::IRBuilder::InsertAddInst, add<std::uint16_t>);
}

TEST_F(JITTestRunner, Int32Addition)
{
    this->TestBinOp<std::int32_t>("add_int32", &city::IRBuilder::InsertAddInst, add<std::int32_t>);
}

TEST_F(JITTestRunner, UInt32Addition)
{
    this->TestBinOp<std::uint32_t>("add_uint32", &city::IRBuilder::InsertAddInst, add<std::uint32_t>);
}

TEST_F(JITTestRunner, Int64Addition)
{
    this->TestBinOp<std::int64_t>("add_int64", &city::IRBuilder::InsertAddInst, add<std::int64_t>);
}

TEST_F(JITTestRunner, UInt64Addition)
{
    this->TestBinOp<std::uint64_t>("add_uint64", &city::IRBuilder::InsertAddInst, add<std::uint64_t>);
}

TEST_F(JITTestRunner, FP32Addition)
{
    this->TestBinOp<float>("add_fp32", &city::IRBuilder::InsertAddInst, add<float>);
}

TEST_F(JITTestRunner, FP64Addition)
{
    this->TestBinOp<double>("add_fp64", &city::IRBuilder::InsertAddInst, add<double>);
}

TEST_F(JITTestRunner, Int16Subtraction)
{
    this->TestBinOp<std::int16_t>("sub_int16", &city::IRBuilder::InsertSubInst, sub<std::int16_t>);
}

TEST_F(JITTestRunner, UInt16Subtraction)
{
    this->TestBinOp<std::uint16_t>("sub_uint16", &city::IRBuilder::InsertSubInst, sub<std::uint16_t>);
}

TEST_F(JITTestRunner, Int32Subtraction)
{
    this->TestBinOp<std::int32_t>("sub_int32", &city::IRBuilder::InsertSubInst, sub<std::int32_t>);
}

TEST_F(JITTestRunner, UInt32Subtraction)
{
    this->TestBinOp<std::uint32_t>("sub_uint32", &city::IRBuilder::InsertSubInst, sub<std::uint32_t>);
}

TEST_F(JITTestRunner, Int64Subtraction)
{
    this->TestBinOp<std::int64_t>("sub_int64", &city::IRBuilder::InsertSubInst, sub<std::int64_t>);
}

TEST_F(JITTestRunner, UInt64Subtraction)
{
    this->TestBinOp<std::uint64_t>("sub_uint64", &city::IRBuilder::InsertSubInst, sub<std::uint64_t>);
}

TEST_F(JITTestRunner, FP32Subtraction)
{
    this->TestBinOp<float>("sub_fp32", &city::IRBuilder::InsertSubInst, sub<float>);
}

TEST_F(JITTestRunner, FP64Subtraction)
{
    this->TestBinOp<double>("sub_fp64", &city::IRBuilder::InsertSubInst, sub<double>);
}

TEST_F(JITTestRunner, Int16Multiplication)
{
    this->TestBinOp<std::int16_t>("mul_int16", &city::IRBuilder::InsertMulInst, mul<std::int16_t>);
}

TEST_F(JITTestRunner, UInt16Multiplication)
{
    this->TestBinOp<std::uint16_t>("mul_uint16", &city::IRBuilder::InsertMulInst, mul<std::uint16_t>);
}

TEST_F(JITTestRunner, Int32Multiplication)
{
    this->TestBinOp<std::int32_t>("mul_int32", &city::IRBuilder::InsertMulInst, mul<std::int32_t>);
}

TEST_F(JITTestRunner, UInt32Multiplication)
{
    this->TestBinOp<std::uint32_t>("mul_uint32", &city::IRBuilder::InsertMulInst, mul<std::uint32_t>);
}

TEST_F(JITTestRunner, Int64Multiplication)
{
    this->TestBinOp<std::int64_t>("mul_int64", &city::IRBuilder::InsertMulInst, mul<std::int64_t>);
}

TEST_F(JITTestRunner, UInt64Multiplication)
{
    this->TestBinOp<std::uint64_t>("mul_uint64", &city::IRBuilder::InsertMulInst, mul<std::uint64_t>);
}

TEST_F(JITTestRunner, FP32Multiplication)
{
    this->TestBinOp<float>("mul_fp32", &city::IRBuilder::InsertMulInst, mul<float>);
}

TEST_F(JITTestRunner, FP64Multiplication)
{
    this->TestBinOp<double>("mul_fp64", &city::IRBuilder::InsertMulInst, mul<double>);
}

TEST_F(JITTestRunner, Int16Division)
{
    this->TestBinOp<std::int16_t>("div_int16", &city::IRBuilder::InsertDivInst, div<std::int16_t>, false);
}

TEST_F(JITTestRunner, UInt16Division)
{
    this->TestBinOp<std::uint16_t>("div_uint16", &city::IRBuilder::InsertDivInst, div<std::uint16_t>, false);
}

TEST_F(JITTestRunner, Int32Division)
{
    this->TestBinOp<std::int32_t>("div_int32", &city::IRBuilder::InsertDivInst, div<std::int32_t>, false);
}

TEST_F(JITTestRunner, UInt32Division)
{
    this->TestBinOp<std::uint32_t>("div_uint32", &city::IRBuilder::InsertDivInst, div<std::uint32_t>, false);
}

TEST_F(JITTestRunner, Int64Division)
{
    this->TestBinOp<std::int64_t>("div_int64", &city::IRBuilder::InsertDivInst, div<std::int64_t>, false);
}

TEST_F(JITTestRunner, UInt64Division)
{
    this->TestBinOp<std::uint64_t>("div_uint64", &city::IRBuilder::InsertDivInst, div<std::uint64_t>, false);
}

TEST_F(JITTestRunner, FP32Division)
{
    this->TestBinOp<float>("div_fp32", &city::IRBuilder::InsertDivInst, div<float>, false);
}

TEST_F(JITTestRunner, FP64Division)
{
    this->TestBinOp<double>("div_fp64", &city::IRBuilder::InsertDivInst, div<double>, false);
}

TEST_F(JITTestRunner, Int16AdditionArgs)
{
    this->TestBinOpArgs<std::int16_t>("add_int16", &city::IRBuilder::InsertAddInst, add<std::int16_t>);
}

TEST_F(JITTestRunner, UInt16AdditionArgs)
{
    this->TestBinOpArgs<std::uint16_t>("add_uint16", &city::IRBuilder::InsertAddInst, add<std::uint16_t>);
}

TEST_F(JITTestRunner, Int32AdditionArgs)
{
    this->TestBinOpArgs<std::int32_t>("add_int32", &city::IRBuilder::InsertAddInst, add<std::int32_t>);
}

TEST_F(JITTestRunner, UInt32AdditionArgs)
{
    this->TestBinOpArgs<std::uint32_t>("add_uint32", &city::IRBuilder::InsertAddInst, add<std::uint32_t>);
}

TEST_F(JITTestRunner, Int64AdditionArgs)
{
    this->TestBinOpArgs<std::int64_t>("add_int64", &city::IRBuilder::InsertAddInst, add<std::int64_t>);
}

TEST_F(JITTestRunner, UInt64AdditionArgs)
{
    this->TestBinOpArgs<std::uint64_t>("add_uint64", &city::IRBuilder::InsertAddInst, add<std::uint64_t>);
}

TEST_F(JITTestRunner, FP32AdditionArgs)
{
    this->TestBinOpArgs<float>("add_fp32", &city::IRBuilder::InsertAddInst, add<float>);
}

TEST_F(JITTestRunner, FP64AdditionArgs)
{
    this->TestBinOpArgs<double>("add_fp64", &city::IRBuilder::InsertAddInst, add<double>);
}

TEST_F(JITTestRunner, Int16SubtractionArgs)
{
    this->TestBinOpArgs<std::int16_t>("sub_int16", &city::IRBuilder::InsertSubInst, sub<std::int16_t>);
}

TEST_F(JITTestRunner, UInt16SubtractionArgs)
{
    this->TestBinOpArgs<std::uint16_t>("sub_uint16", &city::IRBuilder::InsertSubInst, sub<std::uint16_t>);
}

TEST_F(JITTestRunner, Int32SubtractionArgs)
{
    this->TestBinOpArgs<std::int32_t>("sub_int32", &city::IRBuilder::InsertSubInst, sub<std::int32_t>);
}

TEST_F(JITTestRunner, UInt32SubtractionArgs)
{
    this->TestBinOpArgs<std::uint32_t>("sub_uint32", &city::IRBuilder::InsertSubInst, sub<std::uint32_t>);
}

TEST_F(JITTestRunner, Int64SubtractionArgs)
{
    this->TestBinOpArgs<std::int64_t>("sub_int64", &city::IRBuilder::InsertSubInst, sub<std::int64_t>);
}

TEST_F(JITTestRunner, UInt64SubtractionArgs)
{
    this->TestBinOpArgs<std::uint64_t>("sub_uint64", &city::IRBuilder::InsertSubInst, sub<std::uint64_t>);
}

TEST_F(JITTestRunner, FP32SubtractionArgs)
{
    this->TestBinOpArgs<float>("sub_fp32", &city::IRBuilder::InsertSubInst, sub<float>);
}

TEST_F(JITTestRunner, FP64SubtractionArgs)
{
    this->TestBinOpArgs<double>("sub_fp64", &city::IRBuilder::InsertSubInst, sub<double>);
}

TEST_F(JITTestRunner, Int16MultiplicationArgs)
{
    this->TestBinOpArgs<std::int16_t>("mul_int16", &city::IRBuilder::InsertMulInst, mul<std::int16_t>);
}

TEST_F(JITTestRunner, UInt16MultiplicationArgs)
{
    this->TestBinOpArgs<std::uint16_t>("mul_uint16", &city::IRBuilder::InsertMulInst, mul<std::uint16_t>);
}

TEST_F(JITTestRunner, Int32MultiplicationArgs)
{
    this->TestBinOpArgs<std::int32_t>("mul_int32", &city::IRBuilder::InsertMulInst, mul<std::int32_t>);
}

TEST_F(JITTestRunner, UInt32MultiplicationArgs)
{
    this->TestBinOpArgs<std::uint32_t>("mul_uint32", &city::IRBuilder::InsertMulInst, mul<std::uint32_t>);
}

TEST_F(JITTestRunner, Int64MultiplicationArgs)
{
    this->TestBinOpArgs<std::int64_t>("mul_int64", &city::IRBuilder::InsertMulInst, mul<std::int64_t>);
}

TEST_F(JITTestRunner, UInt64MultiplicationArgs)
{
    this->TestBinOpArgs<std::uint64_t>("mul_uint64", &city::IRBuilder::InsertMulInst, mul<std::uint64_t>);
}

TEST_F(JITTestRunner, FP32MultiplicationArgs)
{
    this->TestBinOpArgs<float>("mul_fp32", &city::IRBuilder::InsertMulInst, mul<float>);
}

TEST_F(JITTestRunner, FP64MultiplicationArgs)
{
    this->TestBinOpArgs<double>("mul_fp64", &city::IRBuilder::InsertMulInst, mul<double>);
}

TEST_F(JITTestRunner, Int16DivisionArgs)
{
    this->TestBinOpArgs<std::int16_t>("div_int16", &city::IRBuilder::InsertDivInst, div<std::int16_t>, false);
}

TEST_F(JITTestRunner, UInt16DivisionArgs)
{
    this->TestBinOpArgs<std::uint16_t>("div_uint16", &city::IRBuilder::InsertDivInst, div<std::uint16_t>, false);
}

TEST_F(JITTestRunner, Int32DivisionArgs)
{
    this->TestBinOpArgs<std::int32_t>("div_int32", &city::IRBuilder::InsertDivInst, div<std::int32_t>, false);
}

TEST_F(JITTestRunner, UInt32DivisionArgs)
{
    this->TestBinOpArgs<std::uint32_t>("div_uint32", &city::IRBuilder::InsertDivInst, div<std::uint32_t>, false);
}

TEST_F(JITTestRunner, Int64DivisionArgs)
{
    this->TestBinOpArgs<std::int64_t>("div_int64", &city::IRBuilder::InsertDivInst, div<std::int64_t>, false);
}

TEST_F(JITTestRunner, UInt64DivisionArgs)
{
    this->TestBinOpArgs<std::uint64_t>("div_uint64", &city::IRBuilder::InsertDivInst, div<std::uint64_t>, false);
}

TEST_F(JITTestRunner, FP32DivisionArgs)
{
    this->TestBinOpArgs<float>("div_fp32", &city::IRBuilder::InsertDivInst, div<float>, false);
}

TEST_F(JITTestRunner, FP64DivisionArgs)
{
    this->TestBinOpArgs<double>("div_fp64", &city::IRBuilder::InsertDivInst, div<double>, false);
}
