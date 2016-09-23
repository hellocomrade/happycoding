//https://codility.com/demo/results/trainingS8ANJ4-GBA/
object SolutionLongestPassword {
  def solution(s: String): Int = {
    def filter(strs: List[String]): List[Int] = for(str <- strs if 1 == (str.length() & 1) && str.forall(_.isLetterOrDigit) && 1 == (str.count(_.isDigit) & 1))yield str.length()
    (-1 :: filter(s.split(" ").toList)).max
  }
}
