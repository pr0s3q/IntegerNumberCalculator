﻿using System.Diagnostics;
using Xunit;

namespace Tests;

public sealed class IntegerNumberCalculatorTests : IDisposable
{
    #region Constructor

    public IntegerNumberCalculatorTests()
    {
        _process = new Process();
        _process.StartInfo =
            new ProcessStartInfo("\"C:\\Code\\C++\\IntegerNumberCalculator\\x64\\Debug\\IntegerNumberCalculator.exe\"")
            {
                RedirectStandardInput = true,
                RedirectStandardOutput = true
            };

        _process.Start();
    }

    #endregion

    #region IDisposable

    /// <inheritdoc />
    public void Dispose()
    {
        _process.Dispose();
    }

    #endregion

    #region Data members

    private readonly Process _process;

    #endregion

    #region Tests

    [Fact]
    public async void Test1()
    {
        await _process.StandardInput.WriteLineAsync("1");
        await _process.StandardInput.WriteLineAsync(
            "MIN ( ( 100 , MAX ( 1 , 34 , 2 ) , 80 ,  MIN ( 66 , 36  , 35 , 77 ) , 50 , 60 ) ) .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal(
            "\r\n100 1 34 2 MAX3 80 66 36 35 77 MIN4 50 60 MIN6 \r\nMAX3 2 34 1 100 \r\nMIN4 77 35 36 66 80 34 100 \r\nMIN6 60 50 35 80 34 100 \r\n34\r\n",
            output);
    }

    [Fact]
    public async void Test2()
    {
        await _process.StandardInput.WriteLineAsync("2");
        await _process.StandardInput.WriteLineAsync(
            "MIN ( ( 100 , MAX ( 1 , 34 , 2 ) , 80 ,  MIN ( 66 , 36  , 35 , 77 ) , 50 , 60 ) ) .");
        await _process.StandardInput.WriteLineAsync(
            "2 + MIN ( 100 , MAX ( 1 , 6 * 5 + 2 , 2 ) , 80 ,  MIN ( 66 , 36  , 35 , 77 ) , 50 , 60 ) * 3 .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal(
            "\r\n100 1 34 2 MAX3 80 66 36 35 77 MIN4 50 60 MIN6 \r\nMAX3 2 34 1 100 \r\nMIN4 77 35 36 66 80 34 100 \r\nMIN6 60 50 35 80 34 100 \r\n34\r\n\r\n2 100 1 6 5 * 2 + 2 MAX3 80 66 36 35 77 MIN4 50 60 MIN6 3 * + \r\n* 5 6 1 100 2 \r\n+ 2 30 1 100 2 \r\nMAX3 2 32 1 100 2 \r\nMIN4 77 35 36 66 80 32 100 2 \r\nMIN6 60 50 35 80 32 100 2 \r\n* 3 32 2 \r\n+ 96 2 \r\n98\r\n",
            output);
    }

    [Fact]
    public async void Test3()
    {
        await _process.StandardInput.WriteLineAsync("1");
        await _process.StandardInput.WriteLineAsync(
            "( ( MIN ( ( 100 , MAX ( ( ( 1 , 34 , 2 ) ) ) , 80 ,  MIN ( 66 , 36  , 35 , 77 ) , 50 , 60 ) ) ) ) .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal(
            "\r\n100 1 34 2 MAX3 80 66 36 35 77 MIN4 50 60 MIN6 \r\nMAX3 2 34 1 100 \r\nMIN4 77 35 36 66 80 34 100 \r\nMIN6 60 50 35 80 34 100 \r\n34\r\n",
            output);
    }

    [Fact]
    public async void Test4()
    {
        await _process.StandardInput.WriteLineAsync("1");
        await _process.StandardInput.WriteLineAsync("N 400 + ( 11 - ( 3 * 2 ) ) / 2 + N N 200 .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal(
            "\r\n400 N 11 3 2 * - 2 / + 200 N N +\nN 400\n* 2 3 11 -400\n- 6 11 -400\n/ 2 5 -400\n+ 2 -400\nN 200 -398\nN -200 -398\n+ 200 -398\n-198\r\n",
            output);
    }

    [Fact]
    public async void Test5()
    {
        await _process.StandardInput.WriteLineAsync("1");
        await _process.StandardInput.WriteLineAsync("N ( ( MAX ( 0 , 1 ) + N ( 1 ) ) ) .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal("\r\n0 1 MAX2 1 N + N\nMAX2 1 0\nN 1 1\n+ -1 1\nN 0\n0\r\n", output);
    }

    [Fact]
    public async void Test6()
    {
        await _process.StandardInput.WriteLineAsync("1");
        await _process.StandardInput.WriteLineAsync(
            "MIN ( MIN ( IF ( 0 , 8 , 2 ) ) , MAX ( MIN ( 9 ) , 4 + 9 ) , ( IF ( 3 , 9 , 9 ) / MIN ( 7 , 0 , 6 , 2 , 1 ) ) , N ( 3 + 4 ) , 1 * 1 + IF ( 1 , 9 , 2 ) ) .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal(
            "\r\n0 8 2 IF MIN1 9 MIN1 4 9 + MAX2 3 9 9 IF 7 0 6 2 1 MIN5 / 3 4 + N 1 1 * 1 9 2 IF + MIN5\nIF 2 8 0\nMIN1 2\nMIN1 9 2\n+ 9 4 9 2\nMAX2 13 9 2\nIF 9 9 3 13 2\nMIN5 1 2 6 0 7 9 13 2\n/ 0 9 13 2\nERROR\r\n",
            output);
    }

    [Fact]
    public async void Test7()
    {
        await _process.StandardInput.WriteLineAsync("1");
        await _process.StandardInput.WriteLineAsync(
            "( MAX ( N ( 2 ) , 3 * 6 , ( 0 * 5 ) , N ( 4 ) , ( 4 - 9 ) ) + MIN ( MIN ( 8 , 0 , 2 , 2 , 0 , 4 ) ) ) .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal(
            "\r\n2 N 3 6 * 0 5 * 4 N 4 9 - MAX5 8 0 2 2 0 4 MIN6 MIN1 +\nN 2\n* 6 3 -2\n* 5 0 18 -2\nN 4 0 18 -2\n- 9 4 -4 0 18 -2\nMAX5 -5 -4 0 18 -2\nMIN6 4 0 2 2 0 8 18\nMIN1 0 18\n+ 0 18\n18\r\n",
            output);
    }

    [Fact]
    public async void Test8()
    {
        await _process.StandardInput.WriteLineAsync("1");
        await _process.StandardInput.WriteLineAsync("N IF ( IF ( 8 , 9 , 6 ) , ( 1 * 2 ) , N 4 ) .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal("\r\n8 9 6 IF 1 2 * 4 N IF N\nIF 6 9 8\n* 2 1 9\nN 4 2 9\nIF -4 2 9\nN 2\n-2\r\n", output);
    }

    [Fact]
    public async void Test9()
    {
        await _process.StandardInput.WriteLineAsync("1");
        await _process.StandardInput.WriteLineAsync("( 9 / 7 ) - IF ( 5 , 5 , 7 ) - ( N 6 - IF ( 8 , 6 , 2 ) ) .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal(
            "\r\n9 7 / 5 5 7 IF - 6 N 8 6 2 IF - -\n/ 7 9\nIF 7 5 5 1\n- 5 1\nN 6 -4\nIF 2 6 8 -6 -4\n- 6 -6 -4\n- -12 -4\n8\r\n",
            output);
    }

    [Fact]
    public async void Test10()
    {
        await _process.StandardInput.WriteLineAsync("1");
        await _process.StandardInput.WriteLineAsync("N ( ( ( 0 * 0 ) + MAX ( 0 , 7 , 9 , 3 ) ) ) .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal("\r\n0 0 * 0 7 9 3 MAX4 + N\n* 0 0\nMAX4 3 9 7 0 0\n+ 9 0\nN 9\n-9\r\n", output);
    }

    [Fact]
    public async void Test11()
    {
        await _process.StandardInput.WriteLineAsync("1");
        await _process.StandardInput.WriteLineAsync("IF ( N 4 , IF ( 3 , 7 , 9 ) , N ( 8 ) ) + N ( 5 * 9 ) .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal(
            "\r\n4 N 3 7 9 IF 8 N IF 5 9 * N +\nN 4\nIF 9 7 3 -4\nN 8 7 -4\nIF -8 7 -4\n* 9 5 -8\nN 45 -8\n+ -45 -8\n-53\r\n",
            output);
    }

    [Fact]
    public async void Test12()
    {
        await _process.StandardInput.WriteLineAsync("1");
        await _process.StandardInput.WriteLineAsync(
            "MIN ( 3 - 9 * 2 / 7 , IF ( 2 + 7 , 0 - 6 , 8 + 0 ) , IF ( 6 * 5 , ( 5 / 8 ) , N ( 6 ) ) , MAX ( 4 , 4 , 4 , 1 ) / 7 * 1 , MIN ( MIN ( 7 , 6 , 0 , 0 , 6 ) , ( 0 * 3 ) , ( 6 * 1 ) , ( 8 + 1 ) ) , ( 7 - 5 + N 4 ) ) .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal(
            "\r\n3 9 2 * 7 / - 2 7 + 0 6 - 8 0 + IF 6 5 * 5 8 / 6 N IF 4 4 4 1 MAX4 7 / 1 * 7 6 0 0 6 MIN5 0 3 * 6 1 * 8 1 + MIN4 7 5 - 4 N + MIN6\n* 2 9 3\n/ 7 18 3\n- 2 3\n+ 7 2 1\n- 6 0 9 1\n+ 0 8 -6 9 1\nIF 8 -6 9 1\n* 5 6 -6 1\n/ 8 5 30 -6 1\nN 6 0 30 -6 1\nIF -6 0 30 -6 1\nMAX4 1 4 4 4 0 -6 1\n/ 7 4 0 -6 1\n* 1 0 0 -6 1\nMIN5 6 0 0 6 7 0 0 -6 1\n* 3 0 0 0 0 -6 1\n* 1 6 0 0 0 0 -6 1\n+ 1 8 6 0 0 0 0 -6 1\nMIN4 9 6 0 0 0 0 -6 1\n- 5 7 0 0 0 -6 1\nN 4 2 0 0 0 -6 1\n+ -4 2 0 0 0 -6 1\nMIN6 -2 0 0 0 -6 1\n-6\r\n",
            output);
    }

    [Fact]
    public async void Test13()
    {
        await _process.StandardInput.WriteLineAsync("1");
        await _process.StandardInput.WriteLineAsync(
            "N IF ( MIN ( 2 , 5 ) , ( 2 * 1 ) , MIN ( 3 , 7 , 3 , 3 , 7 , 5 ) ) .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal(
            "\r\n2 5 MIN2 2 1 * 3 7 3 3 7 5 MIN6 IF N\nMIN2 5 2\n* 1 2 2\nMIN6 5 7 3 3 7 3 2 2\nIF 3 2 2\nN 2\n-2\r\n",
            output);
    }

    [Fact]
    public async void Test14()
    {
        await _process.StandardInput.WriteLineAsync("1");
        await _process.StandardInput.WriteLineAsync(
            "MAX ( IF ( 8 , 6 , 0 ) , ( 5 + 0 ) , IF ( 0 , 0 , 5 ) , MIN ( 4 ) ) - N 7 * 5 .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal(
            "\r\n8 6 0 IF 5 0 + 0 0 5 IF 4 MIN1 MAX4 7 N 5 * -\nIF 0 6 8\n+ 0 5 6\nIF 5 0 0 5 6\nMIN1 4 5 5 6\nMAX4 4 5 5 6\nN 7 6\n* 5 -7 6\n- -35 6\n41\r\n",
            output);
    }

    [Fact]
    public async void Test15()
    {
        await _process.StandardInput.WriteLineAsync("1");
        await _process.StandardInput.WriteLineAsync("( MAX ( 0 ) + ( 4 - 1 ) ) + ( IF ( 3 , 7 , 3 ) + ( 8 - 7 ) ) .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal(
            "\r\n0 MAX1 4 1 - + 3 7 3 IF 8 7 - + +\nMAX1 0\n- 1 4 0\n+ 3 0\nIF 3 7 3 3\n- 7 8 7 3\n+ 1 7 3\n+ 8 3\n11\r\n",
            output);
    }

    [Fact]
    public async void Test16()
    {
        await _process.StandardInput.WriteLineAsync("1");
        await _process.StandardInput.WriteLineAsync(
            "IF ( ( N ( 7 ) / N ( 6 ) ) , ( 1 + 3 / N 0 ) , ( 2 / 2 ) / MIN ( 1 , 7 ) ) .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal(
            "\r\n7 N 6 N / 1 3 0 N / + 2 2 / 1 7 MIN2 / IF\nN 7\nN 6 -7\n/ -6 -7\nN 0 3 1 1\n/ 0 3 1 1\nERROR\r\n",
            output);
    }

    [Fact]
    public async void Test17()
    {
        await _process.StandardInput.WriteLineAsync("1");
        await _process.StandardInput.WriteLineAsync("( 2 + 6 + ( 5 / 5 ) * MIN ( IF ( 3 , 8 , 3 ) ) ) .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal(
            "\r\n2 6 + 5 5 / 3 8 3 IF MIN1 * +\n+ 6 2\n/ 5 5 8\nIF 3 8 3 1 8\nMIN1 8 1 8\n* 8 1 8\n+ 8 8\n16\r\n",
            output);
    }

    [Fact]
    public async void Test18()
    {
        await _process.StandardInput.WriteLineAsync("1");
        await _process.StandardInput.WriteLineAsync("N ( ( 0 / 7 ) / 4 + 3 ) .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal("\r\n0 7 / 4 / 3 + N\n/ 7 0\n/ 4 0\n+ 3 0\nN 3\n-3\r\n", output);
    }

    [Fact]
    public async void Test19()
    {
        await _process.StandardInput.WriteLineAsync("1");
        await _process.StandardInput.WriteLineAsync(
            "IF ( ( 5 + 6 / N ( 4 ) ) , MIN ( ( 1 - 7 ) , 0 / 6 , 6 + 4 , 9 / 1 , 0 - 4 , N 1 ) , N ( 2 * 2 ) ) .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal(
            "\r\n5 6 4 N / + 1 7 - 0 6 / 6 4 + 9 1 / 0 4 - 1 N MIN6 2 2 * N IF\nN 4 6 5\n/ -4 6 5\n+ -1 5\n- 7 1 4\n/ 6 0 -6 4\n+ 4 6 0 -6 4\n/ 1 9 10 0 -6 4\n- 4 0 9 10 0 -6 4\nN 1 -4 9 10 0 -6 4\nMIN6 -1 -4 9 10 0 -6 4\n* 2 2 -6 4\nN 4 -6 4\nIF -4 -6 4\n-6\r\n",
            output);
    }

    [Fact]
    public async void Test20()
    {
        await _process.StandardInput.WriteLineAsync("1");
        await _process.StandardInput.WriteLineAsync("N ( ( ( 7 + 4 ) + ( 6 / 3 ) ) ) .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal("\r\n7 4 + 6 3 / + N\n+ 4 7\n/ 3 6 11\n+ 2 11\nN 13\n-13\r\n", output);
    }

    [Fact]
    public async void Test21()
    {
        await _process.StandardInput.WriteLineAsync("1");
        await _process.StandardInput.WriteLineAsync(
            "IF ( IF ( 7 , 9 , 5 ) / IF ( 8 , 2 , 5 ) , MIN ( IF ( 6 , 0 , 8 ) , N 0 , ( 3 / 0 ) ) , ( 8 - 6 / ( 9 - 9 ) ) ) .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal(
            "\r\n7 9 5 IF 8 2 5 IF / 6 0 8 IF 0 N 3 0 / MIN3 8 6 9 9 - / - IF\nIF 5 9 7\nIF 5 2 8 9\n/ 2 9\nIF 8 0 6 4\nN 0 0 4\n/ 0 3 0 0 4\nERROR\r\n",
            output);
    }

    [Fact]
    public async void Test22()
    {
        await _process.StandardInput.WriteLineAsync("1");
        await _process.StandardInput.WriteLineAsync("( 5 - 4 ) / N 4 / N ( 0 + 9 ) .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal("\r\n5 4 - 4 N / 0 9 + N /\n- 4 5\nN 4 1\n/ -4 1\n+ 9 0 0\nN 9 0\n/ -9 0\n0\r\n", output);
    }

    [Fact]
    public async void Test23()
    {
        await _process.StandardInput.WriteLineAsync("1");
        await _process.StandardInput.WriteLineAsync("N ( MIN ( 1 , 1 , 6 , 1 , 7 ) + N ( 8 ) ) .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal("\r\n1 1 6 1 7 MIN5 8 N + N\nMIN5 7 1 6 1 1\nN 8 1\n+ -8 1\nN -7\n7\r\n", output);
    }

    #endregion
}