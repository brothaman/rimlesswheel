# Created by Octave 4.2.1, Mon Mar 05 22:31:17 2018 CST <rbrothers@Roberts-MacBook-Air.local>
# name: phidot_
# type: class
# classname: sym
# length: 6
# name: ascii
# type: cell
# rows: 1
# columns: 1
# name: <cell-element>
# type: sq_string
# elements: 1
# length: 44
[  0   ]
[      ]
[  0   ]
[      ]
[phidot]





# name: extra
# type: cell
# rows: 1
# columns: 1
# name: <cell-element>
# type: matrix
# rows: 0
# columns: 0





# name: flat
# type: cell
# rows: 1
# columns: 1
# name: <cell-element>
# type: sq_string
# elements: 1
# length: 28
Matrix([[0], [0], [phidot]])





# name: pickle
# type: cell
# rows: 1
# columns: 1
# name: <cell-element>
# type: sq_string
# elements: 1
# length: 79
MutableDenseMatrix([[Integer(0)], [Integer(0)], [Symbol('phidot', real=True)]])





# name: size
# type: cell
# rows: 1
# columns: 1
# name: <cell-element>
# type: matrix
# rows: 1
# columns: 2
 3 1





# name: unicode
# type: cell
# rows: 1
# columns: 1
# name: <cell-element>
# type: sq_string
# elements: 1
# length: 46
⎡0 ⎤
⎢  ⎥
⎢0 ⎥
⎢  ⎥
⎣φ̇⎦







# name: phidoubledot_
# type: class
# classname: sym
# length: 6
# name: ascii
# type: cell
# rows: 1
# columns: 1
# name: <cell-element>
# type: sq_string
# elements: 1
# length: 984
                                                                                                        2                                    2                                2                     
3*g*m1*sin(phi) - g*m1*sin(phi + 2*theta) + 3*g*m2*sin(phi) - g*m2*sin(phi + 2*theta) - 2*l1*m1*thetadot *sin(phi + theta) - 2*l1*m2*thetadot *sin(phi + theta) - l2*m2*phidot *sin(2*phi + 2*theta)
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                                                                    /           2                  \                                                                                
                                                                               2*l2*\m1 - m2*cos (phi + theta) + m2/                                                                                





# name: extra
# type: cell
# rows: 1
# columns: 1
# name: <cell-element>
# type: matrix
# rows: 0
# columns: 0





# name: flat
# type: cell
# rows: 1
# columns: 1
# name: <cell-element>
# type: sq_string
# elements: 1
# length: 246
(3*g*m1*sin(phi) - g*m1*sin(phi + 2*theta) + 3*g*m2*sin(phi) - g*m2*sin(phi + 2*theta) - 2*l1*m1*thetadot**2*sin(phi + theta) - 2*l1*m2*thetadot**2*sin(phi + theta) - l2*m2*phidot**2*sin(2*phi + 2*theta))/(2*l2*(m1 - m2*cos(phi + theta)**2 + m2))





# name: pickle
# type: cell
# rows: 1
# columns: 1
# name: <cell-element>
# type: sq_string
# elements: 1
# length: 1350
Mul(Rational(1, 2), Pow(Symbol('l2', real=True), Integer(-1)), Pow(Add(Symbol('m1', real=True), Mul(Integer(-1), Symbol('m2', real=True), Pow(cos(Add(Symbol('phi', real=True), Symbol('theta', real=True))), Integer(2))), Symbol('m2', real=True)), Integer(-1)), Add(Mul(Integer(3), Symbol('g', real=True), Symbol('m1', real=True), sin(Symbol('phi', real=True))), Mul(Integer(-1), Symbol('g', real=True), Symbol('m1', real=True), sin(Add(Symbol('phi', real=True), Mul(Integer(2), Symbol('theta', real=True))))), Mul(Integer(3), Symbol('g', real=True), Symbol('m2', real=True), sin(Symbol('phi', real=True))), Mul(Integer(-1), Symbol('g', real=True), Symbol('m2', real=True), sin(Add(Symbol('phi', real=True), Mul(Integer(2), Symbol('theta', real=True))))), Mul(Integer(-1), Integer(2), Symbol('l1', real=True), Symbol('m1', real=True), Pow(Symbol('thetadot', real=True), Integer(2)), sin(Add(Symbol('phi', real=True), Symbol('theta', real=True)))), Mul(Integer(-1), Integer(2), Symbol('l1', real=True), Symbol('m2', real=True), Pow(Symbol('thetadot', real=True), Integer(2)), sin(Add(Symbol('phi', real=True), Symbol('theta', real=True)))), Mul(Integer(-1), Symbol('l2', real=True), Symbol('m2', real=True), Pow(Symbol('phidot', real=True), Integer(2)), sin(Add(Mul(Integer(2), Symbol('phi', real=True)), Mul(Integer(2), Symbol('theta', real=True)))))))





# name: size
# type: cell
# rows: 1
# columns: 1
# name: <cell-element>
# type: matrix
# rows: 1
# columns: 2
 1 1





# name: unicode
# type: cell
# rows: 1
# columns: 1
# name: <cell-element>
# type: sq_string
# elements: 1
# length: 1138
                                                                                  2                        2                      2               
3⋅g⋅m₁⋅sin(φ) - g⋅m₁⋅sin(φ + 2⋅θ) + 3⋅g⋅m₂⋅sin(φ) - g⋅m₂⋅sin(φ + 2⋅θ) - 2⋅l₁⋅m₁⋅θ̇ ⋅sin(φ + θ) - 2⋅l₁⋅m₂⋅θ̇ ⋅sin(φ + θ) - l₂⋅m₂⋅φ̇ ⋅sin(2⋅φ + 2⋅θ)
──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
                                                              ⎛           2            ⎞                                                          
                                                         2⋅l₂⋅⎝m₁ - m₂⋅cos (φ + θ) + m₂⎠                                                          







# name: thetadot_
# type: class
# classname: sym
# length: 6
# name: ascii
# type: cell
# rows: 1
# columns: 1
# name: <cell-element>
# type: sq_string
# elements: 1
# length: 54
[   0    ]
[        ]
[   0    ]
[        ]
[thetadot]





# name: extra
# type: cell
# rows: 1
# columns: 1
# name: <cell-element>
# type: matrix
# rows: 0
# columns: 0





# name: flat
# type: cell
# rows: 1
# columns: 1
# name: <cell-element>
# type: sq_string
# elements: 1
# length: 30
Matrix([[0], [0], [thetadot]])





# name: pickle
# type: cell
# rows: 1
# columns: 1
# name: <cell-element>
# type: sq_string
# elements: 1
# length: 81
MutableDenseMatrix([[Integer(0)], [Integer(0)], [Symbol('thetadot', real=True)]])





# name: size
# type: cell
# rows: 1
# columns: 1
# name: <cell-element>
# type: matrix
# rows: 1
# columns: 2
 3 1





# name: unicode
# type: cell
# rows: 1
# columns: 1
# name: <cell-element>
# type: sq_string
# elements: 1
# length: 46
⎡0 ⎤
⎢  ⎥
⎢0 ⎥
⎢  ⎥
⎣θ̇⎦







# name: thetadoubledot_
# type: class
# classname: sym
# length: 6
# name: ascii
# type: cell
# rows: 1
# columns: 1
# name: <cell-element>
# type: sq_string
# elements: 1
# length: 944
                                                                               2                                                      
                   3*g*m2*sin(theta)   g*m2*sin(2*phi + theta)   l1*m2*thetadot *sin(2*phi + 2*theta)               2                 
-g*m1*sin(theta) - ----------------- + ----------------------- - ------------------------------------ - l2*m2*phidot *sin(phi + theta)
                           2                      2                               2                                                   
--------------------------------------------------------------------------------------------------------------------------------------
                                                    /           2                  \                                                  
                                                 l1*\m1 - m2*cos (phi + theta) + m2/                                                  





# name: extra
# type: cell
# rows: 1
# columns: 1
# name: <cell-element>
# type: matrix
# rows: 0
# columns: 0





# name: flat
# type: cell
# rows: 1
# columns: 1
# name: <cell-element>
# type: sq_string
# elements: 1
# length: 186
(-g*m1*sin(theta) - 3*g*m2*sin(theta)/2 + g*m2*sin(2*phi + theta)/2 - l1*m2*thetadot**2*sin(2*phi + 2*theta)/2 - l2*m2*phidot**2*sin(phi + theta))/(l1*(m1 - m2*cos(phi + theta)**2 + m2))





# name: pickle
# type: cell
# rows: 1
# columns: 1
# name: <cell-element>
# type: sq_string
# elements: 1
# length: 1023
Mul(Pow(Symbol('l1', real=True), Integer(-1)), Pow(Add(Symbol('m1', real=True), Mul(Integer(-1), Symbol('m2', real=True), Pow(cos(Add(Symbol('phi', real=True), Symbol('theta', real=True))), Integer(2))), Symbol('m2', real=True)), Integer(-1)), Add(Mul(Integer(-1), Symbol('g', real=True), Symbol('m1', real=True), sin(Symbol('theta', real=True))), Mul(Integer(-1), Rational(3, 2), Symbol('g', real=True), Symbol('m2', real=True), sin(Symbol('theta', real=True))), Mul(Rational(1, 2), Symbol('g', real=True), Symbol('m2', real=True), sin(Add(Mul(Integer(2), Symbol('phi', real=True)), Symbol('theta', real=True)))), Mul(Integer(-1), Rational(1, 2), Symbol('l1', real=True), Symbol('m2', real=True), Pow(Symbol('thetadot', real=True), Integer(2)), sin(Add(Mul(Integer(2), Symbol('phi', real=True)), Mul(Integer(2), Symbol('theta', real=True))))), Mul(Integer(-1), Symbol('l2', real=True), Symbol('m2', real=True), Pow(Symbol('phidot', real=True), Integer(2)), sin(Add(Symbol('phi', real=True), Symbol('theta', real=True))))))





# name: size
# type: cell
# rows: 1
# columns: 1
# name: <cell-element>
# type: matrix
# rows: 1
# columns: 2
 1 1





# name: unicode
# type: cell
# rows: 1
# columns: 1
# name: <cell-element>
# type: sq_string
# elements: 1
# length: 1076
                                                           2                                      
               3⋅g⋅m₂⋅sin(θ)   g⋅m₂⋅sin(2⋅φ + θ)   l₁⋅m₂⋅θ̇ ⋅sin(2⋅φ + 2⋅θ)           2           
-g⋅m₁⋅sin(θ) - ───────────── + ───────────────── - ──────────────────────── - l₂⋅m₂⋅φ̇ ⋅sin(φ + θ)
                     2                 2                      2                                   
──────────────────────────────────────────────────────────────────────────────────────────────────
                                     ⎛           2            ⎞                                   
                                  l₁⋅⎝m₁ - m₂⋅cos (φ + θ) + m₂⎠                                   







