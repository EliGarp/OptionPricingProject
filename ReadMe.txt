####This is a rudimentary option pricer####

Features:

1. Calls alphavantage api to retrieve daily stock data
2. Has adjustable parameters 
3. Returns alphavantage response as a string
4. Parses string into a Stock object
5. Calculates Option Prices based on the Black Scholes pricing model on One Factor Plain Options 
(though there are headers files for Perpetual Options as well).
6. Outputs results to Excel (Excel must be installed).

To use:

1. Create a free account at https://www.alphavantage.co and get an APIKey
2. Insert your API key at line 95 on TestMain.cpp
3. You need to have Excel.
4. In the file PrintOptions\PrintOptions\UtilitiesDJD\ExcelDriver\ExcelImports.cpp you need to fix the links 
starting on Line 69 to match where your MSO.DLL, EXCEL.exe, and VBE6EXT.OLB are located (though they should be
in a similar location to what I have linked).
5. To change parameters navigate to line 92 on TestMain.cpp where you can set the stock symbol, outputsize, apikey, and the number of days the option is for.
6. Link boost (download boost and then include your boost directory in additional include directories)
7. If you need help installing curl with VS 2017 check my stackoverflow question here: https://stackoverflow.com/questions/47878888/getting-curl-to-work-with-visual-studios-2017.
