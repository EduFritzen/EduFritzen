import System.CPUTime
import System.Environment

lcg2 :: Integer -> [Integer]
lcg2 s = map (`div` 2^16) $ tail $ iterate (\n -> (214013 * n + 2531011) `mod` 2^31) s

main :: IO()
main = do
  seed <- getCPUTime
  let randoms2 = take 10 (lcg2 (seed))
  print randoms2