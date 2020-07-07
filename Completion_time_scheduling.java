/*You are given a file describes a set of jobs with positive and integral weights and lengths.
Your task in this problem is to run the greedy algorithm that schedules jobs in decreasing order of the difference (weight - length). Recall from lecture that this algorithm is not always optimal. IMPORTANT: if two jobs have equal difference (weight - length), you should schedule the job with higher weight first. Beware: if you break ties in a different way, you are likely to get the wrong answer. You should report the sum of weighted completion times of the resulting schedule --- a positive integer
*/
import java.io.File;
import java.math.BigInteger;
import java.util.Scanner;
import java.util.Random;


public class Completion_time_scheduling{
    public class job{
        private int weight, len, difference;
        private double ratio;

        public void set(int w, int l)
        {
            this.weight = w;
            this.len = l;
            this.difference = w - l;
            this.ratio = (double)w / (double)l;
        }

        public int getWeight()
        {
            return this.weight;
        }

        public int getLen()
        {
            return this.len;
        }

        public int getDifference()
        {
            return this.difference;
        }

        public double getRatio()
        {
            return this.ratio;
        }
    }

    private void singleSort_difference(job[] jobAry, int l, int r)
    {
        if (l >= r)
        {
            return;
        }
        job pivot = jobAry[l];
        int i = l;
        int j = r;
        while (i < j)
        {
            while (j>i && jobAry[j].getDifference()>=pivot.getDifference())
            {
                if (jobAry[j].getDifference() == pivot.getDifference() && jobAry[j].getWeight() < pivot.getWeight())
                {
                    break;
                }
                j--;
            }
            jobAry[i] = jobAry[j];
            while (i<j && jobAry[i].getDifference()<=pivot.getDifference())
            {
                if (jobAry[i].getDifference() == pivot.getDifference() && jobAry[i].getWeight() > pivot.getWeight())
                {
                    break;
                }
                i++;
            }
            jobAry[j] = jobAry[i];
        }
        jobAry[i] = pivot;
        singleSort_difference(jobAry, l, i-1);
        singleSort_difference(jobAry, i+1, r);
    }

    private void singleSort_ratio(job[] jobAry, int l, int r)
    {
        if (l >= r)
        {
            return;
        }
        job pivot = jobAry[l];
        int i = l;
        int j = r;
        while (i < j)
        {
            while (j>i && jobAry[j].getRatio()>=pivot.getRatio())//jobAry[j].getDifference()>=pivot.getDifference())
            {
/*
                if (jobAry[j].getDifference() == pivot.getDifference() && jobAry[j].getWeight() < pivot.getWeight())
                {
                    break;
                }*/
                j--;
            }
            jobAry[i] = jobAry[j];
            while (i<j && jobAry[i].getRatio()<=pivot.getRatio())//jobAry[i].getDifference()<=pivot.getDifference())
            {
/*
                if (jobAry[i].getDifference() == pivot.getDifference() && jobAry[i].getWeight() > pivot.getWeight())
                {
                    break;
                }*/
                i++;
            }
            jobAry[j] = jobAry[i];
        }
        jobAry[i] = pivot;
        singleSort_ratio(jobAry, l, i-1);
        singleSort_ratio(jobAry, i+1, r);
    }

    private job[] quickSortJob(job[] jobAry, boolean ascending)
    {
        int left=0;
        int right = jobAry.length-1;
        // choose a random job from array and swap to first (O(nlogn))
        Random rand = new Random();
        int idx_pivot = rand.nextInt(jobAry.length);
        job tempJob = jobAry[0];
        job pivot = jobAry[idx_pivot];
        jobAry[0] = pivot;
        jobAry[idx_pivot] = tempJob;

        //this.singleSort_difference(jobAry, left, right);
        this.singleSort_ratio(jobAry, left, right);
        if (ascending)
        {
            return jobAry;
        }
        else
        {
            // reverse array
            for (int l=0, r=jobAry.length-1; l<r; l++, r--)
            {
                tempJob = jobAry[l];
                jobAry[l] = jobAry[r];
                jobAry[r] = tempJob;
            }
            return jobAry;
        }
    }

    public void run () throws Exception
    {
        // read data
        /*This file describes a set of jobs with positive and integral weights and lengths. It has the format:

        [number_of_jobs]

        [job_1_weight] [job_1_length]

        [job_2_weight] [job_2_length]

        ...

        For example, the third line of the file is "74 59", indicating that the second job has weight 74 and length 59.*/
        File bufferJob = new File("data/jobs.txt");
        Scanner sc = new Scanner("a ");
        try {
            sc = new Scanner(bufferJob);
        }
        catch (Exception e)
        {
            e.printStackTrace();
            System.exit(-1);
        }
        // read lines of data, located in the first line as integer
        int maxLine = sc.nextInt();
        int w, l;

        job[] jobAry = new job[maxLine];
        for (int i=0; i<maxLine; i++)
        {
            w = sc.nextInt();
            l = sc.nextInt();
            jobAry[i] = new job();
            jobAry[i].set(w, l);
        }
        sc.close();

        job[] decendingJob;
        decendingJob = quickSortJob(jobAry, false);
        BigInteger sumCompletion = BigInteger.ZERO;
        BigInteger sumElapse = BigInteger.ZERO;
        for (int i=0; i<decendingJob.length; i++)
        {
//            System.out.print(decendingJob[i].getRatio()+" ");
//            System.out.println(decendingJob[i].getWeight()+"/"+decendingJob[i].getLen());
            sumElapse = sumElapse.add(BigInteger.valueOf(jobAry[i].getLen()));
            sumCompletion = sumCompletion.add(sumElapse.multiply(BigInteger.valueOf(jobAry[i].getWeight())));
        }
        System.out.println(sumCompletion);
    }


    public static void main(String[] args) {
        try {
            completion_time_scheduling obj = new completion_time_scheduling();
            obj.run();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
