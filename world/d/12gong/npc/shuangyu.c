// by happ@YSZZ
 
inherit NPC;
#include "star.h"
 
void create()
{
        set_name("�����޵�", ({"aphrodite", "shuang yu"}));
        set("long", "�ų���������ʥ��ʿ������õ��Ϊ������Ҳ�ǱȽ�а��Ļƽ�ʥ
��ʿ������ڤ��֮ս����Ϊ�ŵ��������� �ػ���˫����.\n");
        set("gender","����");
        set("title", "��"+HIY"�ƽ�ʥ��ʿ"+NOR"��");
        set("age",37);
        set("con",60);
        set("per",32);
        set("str",80);
        set("int",80);
        set("combat_exp",10000000);
        set("daoxing",10000000);
        set("chat_chance",20);
        set("chat_msg", ({
                "�����޵�˵��������˭�ܴ����ƽ�ʮ�����õ��ƽ�ʥ����?\n"   
        }));
        set_skill("dodge", 300);
        set("cant_be_smashed",1);
        set("attitude", "friendly");
        set_skill("force", 300);
        set_skill("parry", 300);
        set_skill("unarmed", 300);
        set_skill("sword", 300);
        set_skill("westsword",300);
        set_skill("boxing",300);
        set_skill("balei",300);
        set_skill("spells",300);
        set_skill("shuangyu", 300);
        map_skill("sword","westsword");
        map_skill("unarmed","boxing");
        map_skill("spells","shuangyu");
        map_skill("dodge","balei");
        set("max_force", 4000);
        set("force", 8000);
        set("max_mana",4000);
        set("mana",8000);
        set("mana_factor",80);
        set("force_factor", 50);
        set("max_kee", 2000);
        set("max_gin", 2000);
        set("max_sen", 2000);
        setup();
        carry_object(__DIR__"obj/sy_cloth")->wear();
        carry_object("/d/obj/weapon/sword/westsword")->wield();
}

void init()
{
        add_action("do_none","perform");
        add_action("do_none","cast");
        add_action("do_none","ji");
}
int do_none()
{
        object me = this_object();
		message_vision("$N��Цһ�������ػ��ŵ���Ů�����Ļƽ𹬵���,����ˣʲô������\n",me);
        return 1;
} 
void check()
{
        object ob=this_object();
        object rose;
        object me2=new("/d/12gong/npc/shuangyu2.c");
		object me=query_temp("my_killer");

        if( ! me ) return ;
  
    if(! present(me,environment()) )
     {
     remove_call_out("check");
     return;
     }                               

     switch(random(6))
     {        
        case 0:
        {
       
         message_vision(HIC"$N����һ����#$%^%!�����һֻ˫ͷ���㣡\n",ob);

        if(random(2)==0)
                {
              message_vision(HIM"�����ſ����죬����$Nһ���˺��\n"NOR,me);
              me->add("eff_kee",-query("max_kee")/10);
              me->add("eff_sen",-query("max_sen")/10);
                }
        else
        message_vision(HIG"$Nһ����ת���Ὺ�����һ����\n"NOR,me);
         }
        break;

        case 2:
        {
       
         if( present("aphrodite two",environment())) return;
      message_vision(HIW"$Nҡ��һ�䣬�ֳ�����һ���Լ�����\n",ob);
      me2->move(environment());
      me2->kill_ob(me);
          
		 }
        
        break;

        case 3:
        {
        rose=new("/d/12gong/npc/obj/rose.c");
        message_vision(HIC"$N��������һֻ��õ�壬ֻ��$N�촽΢������õ�������ҵļ�����$n��\n"NOR,ob,me);
        rose->move(environment(this_object()));

         if(random(3)==0)
                {
              message_vision(HIM"$N����õ��Ķ��̴��������壡\n");
              me->add("eff_kee",-query("max_kee")/10);
              me->add("eff_sen",-query("max_sen")/10);
              rose->move(environment());
                }
        else
        
        message_vision(HIG"$N��׼��õ������ķ���˳�ƽ�ס�˺�õ�壡\n"NOR,me);
        rose->move(me);

         }
        break;

  }
        if( random(3) == 1 )
        powerup();

        remove_call_out("check");
        call_out("check",2+random(3));
}
void die()
{

        object ob = query_temp("my_killer");

        if((ob&&ob->query("12gong/baoping")=="done") && (ob&&ob->query("12gong/shuangyu")!="done"))
        {
        ob->start_busy(3);
        message("chat",HIY+"���ƽ�ʮ�������ŵ���(Athena):"+ob->name()+
        "���ڴ����˻ƽ�ʮ������\n"NOR,users());
        ob->set("12gong/shuangyu","done");
        ob->add("12gong/number",1);
     ob->add("daoxing", 10000);
        tell_object(ob,"��Ӯ����ʮ�����");
        }
       ::die();
}