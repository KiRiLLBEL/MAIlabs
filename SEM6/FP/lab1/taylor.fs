let f x : float = float(System.Math.Log(1. + x - 2. * x * x))

let rec while_impl cond func value =
    if cond value then
        while_impl cond func (func value)
    else 
        value

let sign x = -1. ** (x + 1.)

let pown x n = x ** n

let dumb_taylor x n acc =
    let value t = (((sign t) * (pown 2. t) - 1.) / t) * (pown x t)
    while_impl (fun (x, y) -> abs(value(y) - value(y - 1.)) >= eps) (fun (x, y) -> (x + value(y), y + 1.)) (acc, n)

let smart_taylor x n acc =
    let update v t = v * (t - 1.) * ((sign t) * (pown 2. t) - 1.) / ((sign (t - 1.)) * (pown 2. (t - 1.)) - 1.) / t * x
    (fun (x, _, z) -> (x, z)) (while_impl (fun (x, y, z) -> abs((update y z) - y) >= eps) (fun (x, y, z) -> (x + (update y z), (update y z), z + 1.)) (acc + x, x, n + 1.))

let solve a b eps step =
    printfn "+-------+-----------+----------------+---------+---------------+---------+"
    printfn "|   x   |  Builtin  |  Smart Taylor  | # terms |  Dumb Taylor  | # terms |"
    let print_value x fx (dv, di) (sv, si) = printfn "| %5.2f | %9.6f |   %10.6f   |   %3.0f   |   %9.6f   |   %3.0f   |" x fx dv di sv si
    let func x = print_value x (f x) (smart_taylor x 1. 0) (dumb_taylor x 1. 0); x + step
    while_impl (fun x-> x <= b) func a |> ignore
    printfn "+-------+-----------+----------------+---------+---------------+---------+"

solve -0.2 0.3 0.000001 0.01
