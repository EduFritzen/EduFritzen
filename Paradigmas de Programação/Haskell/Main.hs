import Text.Printf
import System.Environment  
import System.IO
type Point     = (Int,Int)
type Circle    = (Point,Int,String)
---------------------------------------
svgRect :: Int -> Int -> Int -> Int -> String -> String 
svgRect x y w h style = 
  printf "<rect x='%d' y='%d' width='%d' height='%d' fill='%s' />\n" x y w h style
---------------------------------------
svgCircle :: Circle -> String
svgCircle ((x, y), r, style) = 
  printf "<circle cx='%d' cy='%d' r='%d' fill='%s' />\n" x y r style
---------------------------------------
genPatternsInLine :: (Int,Int) -> [Circle]
genPatternsInLine (0,j) = []
genPatternsInLine (n,j) = ((x, y), r, style) : genPatternsInLine(n-1, j)
  where x = 50 + (100*(j-1))
        y = 50 + (100*(n-1))
        r = 25
        style = "black"
---------------------------------------
genPatternsInLine2 :: (Int,Int) -> [Circle]
genPatternsInLine2 (0,j) = []
genPatternsInLine2 (n,j) = ((x, y), r, style) : genPatternsInLine2(n-1, j)
  where x = 0 + (100*(j-1))
        y = 0 + (100*(n-1))
        r = 25
        style = "blue"
---------------------------------------
svgPattern :: [Circle] -> [String]
svgPattern [] = []
svgPattern (x:xs) = svgCircle x : svgPattern xs
---------------------------------------
svgColunas :: Int -> Int -> [String]
svgColunas i 0 = []
svgColunas i j = concat (svgPattern (genPatternsInLine (i,j))) : svgColunas i (j-1)
---------------------------------------
svgColunas2 :: Int -> Int -> [String]
svgColunas2 i 0 = []
svgColunas2 i j = concat (svgPattern (genPatternsInLine2 (i,j))) : svgColunas2 i (j-1)
---------------------------------------
svgBegin :: Float -> Float -> String
svgBegin w h = printf "<svg width='%.2f' height='%.2f' xmlns='http://www.w3.org/2000/svg'>\n" w h 
---------------------------------------
svgEnd :: String
svgEnd = "</svg>"
---------------------------------------
main :: IO ()
main = do 
  putStrLn "Digite dois números: "   
  args <- getLine
  let w = read (args)::Float
      h = 1000
      svgfigs = concat (svgColunas 10 10)
      svgfigs2 = concat (svgColunas2 11 11)
      svgstrs = svgBegin w h ++ 
                svgRect 0 0 1000 1000 "white"  ++
                svgfigs ++
                svgfigs2 ++
                svgEnd
  writeFile "rects.svg" $ svgstrs