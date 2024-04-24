using System.Diagnostics;
using Xunit;

public sealed class IntegerNumberCalculatorTests : IDisposable
{
    #region Constructor

    public IntegerNumberCalculatorTests()
    {
        _process = new Process();
        _process.StartInfo = new ProcessStartInfo("\"C:\\Code\\C++\\IntegerNumberCalculator\\x64\\Debug\\IntegerNumberCalculator.exe\"")
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
        await _process.StandardInput.WriteLineAsync("MIN ( ( 100 , MAX ( 1 , 34 , 2 ) , 80 ,  MIN ( 66 , 36  , 35 , 77 ) , 50 , 60 ) ) .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal("\r\n100 1 34 2 MAX3 80 66 36 35 77 MIN4 50 60 MIN6 \r\nMAX3 2 34 1 100 \r\nMIN4 77 35 36 66 80 34 100 \r\nMIN6 60 50 35 80 34 100 \r\n34\r\n", output);
    }

    [Fact]
    public async void Test2()
    {
        await _process.StandardInput.WriteLineAsync("2");
        await _process.StandardInput.WriteLineAsync("MIN ( ( 100 , MAX ( 1 , 34 , 2 ) , 80 ,  MIN ( 66 , 36  , 35 , 77 ) , 50 , 60 ) ) .");
        await _process.StandardInput.WriteLineAsync("2 + MIN ( 100 , MAX ( 1 , 6 * 5 + 2 , 2 ) , 80 ,  MIN ( 66 , 36  , 35 , 77 ) , 50 , 60 ) * 3 .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal("\r\n100 1 34 2 MAX3 80 66 36 35 77 MIN4 50 60 MIN6 \r\nMAX3 2 34 1 100 \r\nMIN4 77 35 36 66 80 34 100 \r\nMIN6 60 50 35 80 34 100 \r\n34\r\n\r\n2 100 1 6 5 * 2 + 2 MAX3 80 66 36 35 77 MIN4 50 60 MIN6 3 * + \r\n* 5 6 1 100 2 \r\n+ 2 30 1 100 2 \r\nMAX3 2 32 1 100 2 \r\nMIN4 77 35 36 66 80 32 100 2 \r\nMIN6 60 50 35 80 32 100 2 \r\n* 3 32 2 \r\n+ 96 2 \r\n98\r\n", output);
    }

    [Fact]
    public async void Test3()
    {
        await _process.StandardInput.WriteLineAsync("1");
        await _process.StandardInput.WriteLineAsync("( ( MIN ( ( 100 , MAX ( ( ( 1 , 34 , 2 ) ) ) , 80 ,  MIN ( 66 , 36  , 35 , 77 ) , 50 , 60 ) ) ) ) .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal("\r\n100 1 34 2 MAX3 80 66 36 35 77 MIN4 50 60 MIN6 \r\nMAX3 2 34 1 100 \r\nMIN4 77 35 36 66 80 34 100 \r\nMIN6 60 50 35 80 34 100 \r\n34\r\n", output);
    }

    [Fact]
    public async void Test4()
    {
        await _process.StandardInput.WriteLineAsync("1");
        await _process.StandardInput.WriteLineAsync("N 400 + ( 11 - ( 3 * 2 ) ) / 2 + N N 200 .");
        var output = await _process.StandardOutput.ReadToEndAsync();

        Assert.Equal("\r\n400 N 11 3 2 * - 2 / + 200 N N +\nN 400\n* 2 3 11 -400\n- 6 11 -400\n/ 2 5 -400\n+ 2 -400\nN 200 -398\nN -200 -398\n+ 200 -398\n-198\r\n", output);
    }

    #endregion
}