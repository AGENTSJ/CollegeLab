import java.util.*;
public class BANKER {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int pno = 3;//process
        int rno = 2;//resource no
        int[][]need =new int[20][20];//needed
        int[]rc = new int[10];//resource count
        int[][]max =new int[20][20];//maximumneededby a process
        int[][]alloc=new int[20][20];//allocated 
        int[]avail = new int[20];//avilable
        int[]finish = new int[20];//finish
        int[][]flex= new int[20][20];
        int flag = 0;

        int i,j,k ,temp =0;

        System.out.println("give the resource count");

        //resource count

        for(i=0;i<rno;i++){
            System.out.println("resouce no :"+i);
            rc[i]=sc.nextInt();
        }

        //max needed
        System.out.println("give the maximum needed by process");
        for(i=0;i<pno;i++){
            for(j=0;j<rno;j++){
                System.out.println("process no :"+i);
                max[i][j]=sc.nextInt();
                
                //if needed more than total

                if(max[i][j]>rc[j]){
                    System.out.println("the need is more than the total avilable resource");
                    System.out.println("give the value again");
                    max[i][j]=sc.nextInt();
                    
                }
            }
        }
        //allocated
        System.out.println("give the resources allocated");
        for(i=0;i<pno;i++){
            for(j=0;j<rno;j++){
                System.out.println("process no :"+ i);
                alloc[i][j]=sc.nextInt();

                if(alloc[i][j]>rc[j]){
                    System.out.println("the allocated is more than the total avilable resource");
                    System.out.println("give the value again");
                    alloc[i][j]=sc.nextInt();
                    
                }
            }
        }
        //needmatrix
        for(i=0;i<pno;i++){
            for(j=0;j<rno;j++){
                need[i][j]=max[i][j]-alloc[i][j];
            }
        }

      

        //set avail available

       for(i=0;i<rno;i++){
        avail[i]=rc[i];
       }

       for(i=0;i<pno;i++){
        for(j=0;j<rno;j++){
            avail[j]=avail[j]-alloc[i][j];
        }
       }
       System.out.println("executed next safe ");

    // setting finish as -1
       for(i=0;i<pno;i++){
        finish[i]=-1;
       }

    //safe check

    for(k=0;k<pno;k++){

        for(i=0;i<pno;i++){
            for(j=0;j<rno;j++){
                if(need[i][j]<=avail[j] && finish[i]==-1){
                    flag=0;
                }
                if(need[i][j]>avail[j]){
                    flag=1;
                    break;
                }
            }
        
                if(flag==0){
                    finish[i]=1;
                    for(j=0;j<rno;j++){
                        avail[j]=avail[j]+alloc[i][j];
                    }
                }
            
        }
    }//safe check end

    for(i=0;i<pno;i++){
        System.out.println(finish[i]);
    }
   

    }//main fn
}