Seven different symbols represent Roman numerals with the following values:

Symbol	Value
I	1
V	5
X	10
L	50
C	100
D	500
M	1000
Roman numerals are formed by appending the conversions of decimal place values from highest to lowest. Converting a decimal place value into a Roman numeral has the following rules:

## If the value does not start with 4 or 9, select the symbol of the maximal value that can be subtracted from the input, append that symbol to the result, subtract its value, and convert the remainder to a Roman numeral.

## If the value starts with 4 or 9 use the subtractive form representing one symbol subtracted from the following symbol, for example, 4 is 1 (I) less than 5 (V): IV and 9 is 1 (I) less than 10 (X): IX. Only the following subtractive forms are used: 4 (IV), 9 (IX), 40 (XL), 90 (XC), 400 (CD) and 900 (CM).

## Only powers of 10 (I, X, C, M) can be appended consecutively at most 3 times to represent multiples of 10. You cannot append 5 (V), 50 (L), or 500 (D) multiple times. If you need to append a symbol 4 times use the subtractive form.
## Given an integer, convert it to a Roman numeral.

 

Example 1:

Input: num = 3749

Output: "MMMDCCXLIX"

Explanation:

3000 = MMM as 1000 (M) + 1000 (M) + 1000 (M)
 700 = DCC as 500 (D) + 100 (C) + 100 (C)
  40 = XL as 10 (X) less of 50 (L)
   9 = IX as 1 (I) less of 10 (X)
Note: 49 is not 1 (I) less of 50 (L) because the conversion is based on decimal places
Example 2:

Input: num = 58

Output: "LVIII"

Explanation:

50 = L
 8 = VIII
Example 3:

Input: num = 1994

Output: "MCMXCIV"

Explanation:

1000 = M
 900 = CM
  90 = XC
   4 = IV
 

Constraints:

1 <= num <= 3999


What the algorithm means:

Input = the number you want to convert (e.g., 58)
Select the maximal value = find the largest Roman numeral value that fits into your input (without exceeding it)
Append that symbol = add that Roman symbol to your result string
Subtract its value = subtract that Roman value from your input number
Remainder = what's left after subtraction (this becomes your new input)
Repeat until the remainder is 0
Example walkthrough: Convert 58 to Roman numerals

Available values: M=1000, CM=900, D=500, CD=400, C=100, XC=90, L=50, XL=40, X=10, IX=9, V=5, IV=4, I=1

Start: input = 58, result = ""
Step 1: Largest value ≤ 58 is L (50)
Append "L" → result = "L"
Subtract: 58 - 50 = 8 ← this is the remainder
Step 2: input = 8, result = "L"
Largest value ≤ 8 is V (5)
Append "V" → result = "LV"
Subtract: 8 - 5 = 3 ← remainder
Step 3: input = 3, result = "LV"
Largest value ≤ 3 is I (1)
Append "I" → result = "LVI"
Subtract: 3 - 1 = 2 ← remainder
Step 4: input = 2, result = "LVI"
Largest value ≤ 2 is I (1)
Append "I" → result = "LVII"
Subtract: 2 - 1 = 1 ← remainder
Step 5: input = 1, result = "LVII"
Largest value ≤ 1 is I (1)
Append "I" → result = "LVIII"
Subtract: 1 - 1 = 0 ← done!
Final answer: 58 = "LVIII"

In summary:

Subtract what from what? Subtract the Roman numeral's value from the current number
Remainder? The result of that subtraction, which you process next
The algorithm keeps eating away at the number by removing the largest Roman value that fits, until nothing is left.


Greedy Decompositon ...
   1. repeatedly remove the largest Roman value <= current number,  append its symbol , subtract symbols value and then repeat until zero
   2. Ordered look up vs associative map : Use a determinitstic descending traversal
   3. Include subtractive forms explicitly .
   4. Store the look up as vector<pair<int,string>> or array <pair<int,const char*>> intialized descending 
   5. Keep the lookup const/static if reused.

   Loop Pattern .
      1. For each pair (value, symbol) in the descending order:
         . while(num>= value) {append symbol to result ; num -= value;}
         this is the inner while which will be the key repeated subtraction pattern.
   Comple