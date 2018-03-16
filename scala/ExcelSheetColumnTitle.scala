package leetcode

//https://leetcode.com/problems/excel-sheet-column-title/description/
object ExcelSheetColumnTitle {
  def convertToTitle(n: Int): String = {
    def convertOctal2Excel26(i: Int): String = {
      if(i < 1) ""
      else convertOctal2Excel26((i - 1) / 26) + ('A'.toInt + (i - 1) % 26).toChar
    }
    convertOctal2Excel26(n)
  }
}
