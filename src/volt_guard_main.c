#include <linux/module.h> <linux/platform_device.h> <linux/fs.h> <linux/cdev.h> <linux/device.h> <linux/slab.h>
#include "volt_guard_uapi.h"
#define DRV_NAME "volt-guard" 
#define DRV_VERSION "0.1.0"
struct volt_guard_dev{struct platform_device*pdev;struct cdev cdev;dev_t devt;struct device*dev;const struct class*class;};
static int vg_open(struct inode*inode,struct file*filp){filp->private_data=container_of(inode->i_cdev,struct volt_guard_dev,cdev);return 0;}
static long vg_ioctl(struct file*filp,unsigned int cmd,unsigned long arg){
    struct volt_guard_dev*dev=filp->private_data;void __user*u=(void __user*)arg;
    struct volt_guard_power_mode pm;struct volt_guard_sensor s;
    switch(cmd){
    case VOLT_GUARD_IOCTL_SET_MODE:
        if(copy_from_user(&pm,u,sizeof(pm)))return -EFAULT;
        dev_info(&dev->pdev->dev,"Set power mode %d (%umW)\n",pm.mode,pm.power_mw);return 0;
    case VOLT_GUARD_IOCTL_GET_MODE:
        pm.mode=1;pm.power_mw=15000;pm.voltage_mv=12000;pm.current_ma=1250;
        if(copy_to_user(u,&pm,sizeof(pm)))return -EFAULT;return 0;
    case VOLT_GUARD_IOCTL_GET_SENSORS:
        s.temp_celsius=45;s.voltage_mv=12000;s.current_ma=800;s.power_mw=9600;
        if(copy_to_user(u,&s,sizeof(s)))return -EFAULT;return 0;
    default:return -ENOTTY;
    }
}
static const struct file_operations vg_fops={.owner=THIS_MODULE,.open=vg_open,.unlocked_ioctl=vg_ioctl,.llseek=no_llseek};
static int vg_probe(struct platform_device*pdev){
    struct volt_guard_dev*dev=devm_kzalloc(&pdev->dev,sizeof(*dev),GFP_KERNEL);if(!dev)return -ENOMEM;
    dev->pdev=pdev;platform_set_drvdata(pdev,dev);
    int r=alloc_chrdev_region(&dev->devt,0,1,DRV_NAME);if(r)return dev_err_probe(&pdev->dev,r,"chrdev\n");
    cdev_init(&dev->cdev,&vg_fops);dev->cdev.owner=THIS_MODULE;
    r=cdev_add(&dev->cdev,dev->devt,1);if(r){unregister_chrdev_region(dev->devt,1);return r;}
    dev->dev=device_create(dev->class,&pdev->dev,dev->devt,dev,DRV_NAME"%u",0);
    if(IS_ERR(dev->dev)){cdev_del(&dev->cdev);unregister_chrdev_region(dev->devt,1);return PTR_ERR(dev->dev);}
    dev_info(&pdev->dev,"Volt Guard v%s\n",DRV_VERSION);return 0;
}
static void vg_remove(struct platform_device*pdev){struct volt_guard_dev*dev=platform_get_drvdata(pdev);device_destroy(dev->class,dev->devt);cdev_del(&dev->cdev);unregister_chrdev_region(dev->devt,1);}
static const struct of_device_id vg_of_match[]={{.compatible="nvidia,tegra234-volt-guard"},{}};
MODULE_DEVICE_TABLE(of,vg_of_match);
static struct platform_driver vg_driver={.probe=vg_probe,.remove=vg_remove,.driver={.name=DRV_NAME,.of_match_table=vg_of_match}};
static const struct class vg_class={.name=DRV_NAME,.owner=THIS_MODULE};
static int __init vg_init(void){int r=class_register(&vg_class);if(r)return r;r=platform_driver_register(&vg_driver);if(r)class_unregister(&vg_class);pr_info("Volt Guard v%s\n",DRV_VERSION);return r;}
static void __exit vg_exit(void){platform_driver_unregister(&vg_driver);class_unregister(&vg_class);}
module_init(vg_init);module_exit(vg_exit);
MODULE_AUTHOR("Sandesh Ghimire <sandesh@soccentric.com>");MODULE_DESCRIPTION("Jetson AGX Orin power management driver");MODULE_LICENSE("GPL v2");MODULE_VERSION(DRV_VERSION);
