# Timely-lang

### 简介
    timely 2.0 是一个静态语言,正在开发中...
   
### 代码模板
```
public class Main:A,B{
    // 隐式类型转换
    private final a:int,b=10,c:char=10
    private name = 10
    // 变量定义没有出是值必须指明类型, 默认访问权限为 private
    a:int
    b:float
    c:int

    // 常量
    public static final x=10;

    // 构造方法
    public fun Main(a:int,b=10){
        while(a){
            
        }

        if(expr){

        }else if(expr){

        }else if(expr){

        }else{

        }

        try{

        }catch e:Exception{
            e.printf()
        }finally{

        }
    }

    //  函数, 默认返回类型隐式转换
    fun print(a:int, b:int,a=10){
        switch a{
            case 1:
                break
            case 2:
                return 10
            default:
                
        }
    }

    //  函数重载, 默认返回类型隐式转换
    public fun print(a:int,b:int,a:int){
        this.print()
    }
}
```

    
 