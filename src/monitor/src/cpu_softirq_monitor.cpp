#include "cpu_softirq_monitor.h"
#include "read_flie.h"

namespace monitor {
    CPUSoftIRQMonitor::CPUSoftIRQMonitor()
        : m_map(std::unordered_map<std::string, SoftIrq>())
    {
    }

    void CPUSoftIRQMonitor::updateOnce(monitor::proto::MonitorInfo* monitorInfo)
    {
        // "cat /proc/softirqs" 读数据
        ReadFile cpu_softirq_file(std::string("/proc/softirqs"));
        std::vector<std::string> cpu_softirq_list{};
        std::vector<std::vector<std::string>> cpu_softirq_lists{};
        while(cpu_softirq_file.readLine(&cpu_softirq_list))
        {
            cpu_softirq_lists.push_back(cpu_softirq_list);
            cpu_softirq_list.clear();
        }

        // 解析读取的cpu_softirq信息
        for(int i=0; i < cpu_softirq_lists[0].size()-1; ++i)
        {
            std::string name = cpu_softirq_lists[0][i];
            SoftIrq softIrq;
            softIrq.cpu_name = name;
            softIrq.hi = std::stoll(cpu_softirq_lists[1][i+1]);
            softIrq.timer = std::stoll(cpu_softirq_lists[2][i+1]);
            softIrq.net_tx = std::stoll(cpu_softirq_lists[3][i+1]);
            softIrq.net_rx = std::stoll(cpu_softirq_lists[4][i+1]);
            softIrq.block = std::stoll(cpu_softirq_lists[5][i+1]);
            softIrq.irq_poll = std::stoll(cpu_softirq_lists[6][i+1]);
            softIrq.tasklet = std::stoll(cpu_softirq_lists[7][i+1]);
            softIrq.sched = std::stoll(cpu_softirq_lists[8][i+1]);
            softIrq.hrtimer = std::stoll(cpu_softirq_lists[9][i+1]);
            softIrq.rcu = std::stoll(cpu_softirq_lists[10][i+1]);
            softIrq.timepoint = boost::chrono::steady_clock::now();

            auto iter = m_map.find(name);
            if(iter != m_map.end())
            {
                SoftIrq &oldSoftIrq = iter->second;
                double period = boost::chrono::duration<double>(softIrq.timepoint - oldSoftIrq.timepoint).count();
                auto softIrq_message = monitorInfo->add_soft_irq();

                softIrq_message->set_cpu(name);
                softIrq_message->set_hi((softIrq.hi - oldSoftIrq.hi) / period);
                softIrq_message->set_timer((softIrq.timer - oldSoftIrq.timer) / period);
                softIrq_message->set_net_tx((softIrq.net_tx - oldSoftIrq.net_tx) / period);
                softIrq_message->set_net_rx((softIrq.net_rx - oldSoftIrq.net_rx) / period);
                softIrq_message->set_block((softIrq.block - oldSoftIrq.block) / period);
                softIrq_message->set_irq_poll((softIrq.irq_poll - oldSoftIrq.irq_poll) / period);
                softIrq_message->set_tasklet((softIrq.tasklet - oldSoftIrq.tasklet) / period);
                softIrq_message->set_sched((softIrq.sched - oldSoftIrq.sched) / period);
                softIrq_message->set_hrtimer((softIrq.hrtimer - oldSoftIrq.hrtimer) / period);
                softIrq_message->set_rcu((softIrq.rcu - oldSoftIrq.rcu) / period);
            }
            m_map[name] = softIrq;
        }
    }
    
}

/*
 CPU0       CPU1       CPU2       CPU3       CPU4       CPU5       CPU6       CPU7       CPU8       CPU9       CPU10      CPU11      CPU12      CPU13      CPU14      CPU15      CPU16      CPU17      CPU18      CPU19      
          HI:          0          0          0          0          0          0          0          0          0          0          0          0          0          0          0          0          0          0          0          0
       TIMER:      82665      35290      68714      34015      87106      41969      63117      36394      52812      24882      59274      20558      83036      26326      60324      20439      56728      28207      60511      31290
      NET_TX:          0          0          0          0          0          0          0          0          1          0          0          0          0          0          0          0          0          0          0          0
      NET_RX:      37435      14070      38021      23437      41256      25026      46493      17933      47458      23888      47548      20637      45489      13307      44476      20867      41460      24269      39218      16992
       BLOCK:       1848       2224       1958       1673       1313        294        252        461        878          5        481        113        221          0        246         98         16         10        781        272
    IRQ_POLL:          0          0          0          0          0          0          0          0          0          0          0          0          0          0          0          0          0          0          0          0
     TASKLET:     359104      46336      72224      50479      46509          0          6          2          4          1         10          3          0          1          1          0          2          0          0          0
       SCHED:     348109     106436     311383      95412     291666     153990     270150      85172     251277      89519     266277      82160     304114      89071     258735      87024     254848      93892     268783      94058
     HRTIMER:          0          0          0          0          0          0          0          0          0          0          0          0          0          0          0          0          0          0          0          0
         RCU:     292554      96523     303372      94487     278947     147022     267137      86294     251459      88788     263011      83330     289341      87679     252471      87636     250113      92536     259577      92229
*/