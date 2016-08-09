# Type replace metafunction
Type replace metafunction can be used like

```
type_replace_t<ToReplace, Replacement, InputType>;
```

Works for many things... :) 

# Execute lambda on tuple
Function that iterates over an std tuple and executes a lambda.

```
std::tuple<std::array<int,3>, std::array<int,5> > bla = { {1,5,8}, {2,9,7,5,4} };
int acc = 0;
execute_lambda_on_tuple(bla, [&](auto& tuple_elem) {
  for(auto e : tuple_elem) acc += e;
});
std::cout << "Sum: " << acc << std::endl;
```
