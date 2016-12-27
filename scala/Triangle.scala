//https://leetcode.com/problems/triangle/
/*
 * Haven't fully tested. Also, an empty Array is not considered as a valid case!
 * 
 * 1. Create a vector by scanning triangles backward from length - 2 to 0 by -1;
 * 2. foldLeft using triangles.last as seed
 * 3. Operator applies DP on memo array and current row and return a new collection as the next memo
 * 
 * Since all collections are immutable and functional first, we generate more temporary arrays here.  Do we always have a larger space profile using Scala than a "regular" programming language?
 * 
 * Not sure what the stream pipeline looks like here. Processing order like Java 8 stream?
 * http://winterbe.com/posts/2014/07/31/java8-stream-tutorial-examples/ 
 */
object Triangle {
  def triangleSolution(triangles : Array[Array[Int]]) : Int = {
    (for(i <- triangles.length - 2 to 0 by -1) yield triangles(i)).foldLeft(triangles.last)((memo : Array[Int], triangle: Array[Int]) => {
      triangle.zipWithIndex.map((pair : (Int, Int)) => math.min(pair._1 + memo(pair._2), pair._1 + memo(pair._2 + 1)))
    })(0)
  }
  def testTriangle() {
    assert(11 == triangleSolution(Array(Array(2), Array(3, 4), Array(6, 5, 7), Array(4, 1, 8, 3))))
    assert(-10 == triangleSolution(Array(Array(-10))))
    assert(-8 == triangleSolution(Array(Array(-10),Array(4,6),Array(2,8,2),Array(-4,-5,-6,3),Array(8,10,20,0,9))))
    //assert(0 == triangleSolution(Array()))
  }
}