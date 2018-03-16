package leetcode

//https://leetcode.com/problems/excel-sheet-column-number/description/
object ExcelSheetColumnNumber {
    def titleToNumber(s: String): Int = {
      s.foldLeft(0)((acc, chr) => {acc * 26 + chr.toInt - 'A'.toInt})  
    }
}
