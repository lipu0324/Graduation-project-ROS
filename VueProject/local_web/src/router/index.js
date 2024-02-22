import { createRouter, createWebHistory } from 'vue-router'
import HomeView from '../views/HomeView.vue'

const routes = [
  {
    path: '/',
    name: 'Home',
    component: HomeView
  },
  {
    path: '/monitor',
    name: 'MonitorView',
    component: () => import('@/views/MonitorView.vue'),
    children: [
      {
        path: 'deep',
        name: 'FpvDeep',
        component:() => import('@/components/MonitorView/fpvDeep.vue')
      },
      {
        path: 'color',
        name: 'FpvColor',
        component: () => import('@/components/MonitorView/fpvColor.vue')
      }
    ]
  },
  {
    path: '/settings',
    name: 'Settings',
    component: () => import('@/views/SettingsView.vue')
  }
]

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes
})

export default router 
