let f1 x = 1.0 - x + sin (x) - log (1.0 + x)
let f2 x = 3.0* x - 14.0 + exp x - exp (-x)
let f3 x = sqrt(1.0 - x) - tan x

let f1' x = -1.0 + cos x - (1.0 / (1.0 + x))
let f2' x = 3.0 + exp x + exp (-x)
let f3' x = -0.5 / sqrt (1.0 - x) - 1.0 / (cos x * cos x)

let g1 x = 0.1 * (f1 x)
let g2 x = -0.1 * (f2 x)
let g3 x = 0.1 * (f3 x)

let rec while_impl cond func value =
    if cond value then
        while_impl cond func (func value)
    else 
        value

let bisectionMethod f a b eps =
    let mid x y = (x + y) / 2.0
    (fun (x, y) -> mid x y) (while_impl (fun (x, y) -> abs (f (mid x y)) >= eps) (fun (x, y) -> if ((f x) * f (mid x y)) < 0.0 then (x, mid x y) else (mid x y, y)) (a, b))

let iterationMethod g x0 eps =
    let f x = x + g x
    while_impl (fun x-> abs ((f x) - x) >= eps) f x0

let newtonMethod f f' x0 eps =
    let step x = x - (f x) / (f' x)
    while_impl (fun x-> abs ((step x) - x) >= eps) step x0

let solve eps =
    printfn "+------+-------------+-------------+-------------+"
    printfn "| func |  bisection  |  iteration  |   newton    |"
    printfn "|  f1  | %10.9f | %10.9f | %10.9f |" (bisectionMethod f1 1 1.5 eps) (iterationMethod g1 0 eps) (newtonMethod f1 f1' 0 eps)
    printfn "|  f2  | %10.9f | %10.9f | %10.9f |" (bisectionMethod f2 1 3 eps) (iterationMethod g2 0 eps) (newtonMethod f2 f2' 0 eps)
    printfn "|  f3  | %10.9f | %10.9f | %10.9f |" (bisectionMethod f3 0 1 eps) (iterationMethod g3 0 eps) (newtonMethod f3 f3' 0 eps)
    printfn "+------+-------------+-------------+-------------+"

solve 0.0000001
